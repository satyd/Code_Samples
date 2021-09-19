import math
import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import statistics as stats

import time


def calcA(a, b):
    return (1. - b) / a


def calcB(a, b):
    return b / (1. - a)


def fact(n):
    r = 1
    while n:
        r *= n
        n -= 1
    return r


def pfx(x, l):
    return l ** x / (math.factorial(x) * math.exp(l))


def calcZ(x, teta1, teta0):
    return math.log(pfx(x, teta1) / pfx(x, teta0))


n = 1000
obses = 1000
steps = 100
teta0 = 64
teta1 = 72
a = 0.05
b = 0.05
A = calcA(a, b)
B = calcB(a, b)
workNum = steps // 2


def drawplot(mas, rotate, name):
    mas = np.array(mas)
    mas = mas.transpose()
    fig = plt.figure()
    axes = Axes3D(fig)
    xval = np.linspace(teta0, teta1, teta1 - teta0 + 1)
    yval = np.linspace(0, 0.5, workNum)
    x, y = np.meshgrid(xval, yval)
    z = mas
    axes.plot_surface(x, y, z, rstride=5, cstride=5, cmap=cm.jet, label=name)
    axes.set_zlabel(name)
    axes.scatter(x, y, z, cmap=cm.jet)
    axes.view_init(rotate[0], rotate[1])
    plt.savefig(name + '.jpg')
    plt.show()


def test(var):
    wrongs = [[]] * (teta1 - teta0 + 1)
    observations = [[]] * (teta1 - teta0 + 1)
    cumWrongs = [[]] * (teta1 - teta0 + 1)
    cumObservations = [[]] * (teta1 - teta0 + 1)
    for tetaR in range(teta0, teta1 + 1):
        # result = [False, 0.]
        cumWrong = 0.
        cumObs = 0.
        wrongs[tetaR - teta0] = [0.] * workNum
        observations[tetaR - teta0] = [0.] * workNum

        cumObservations[tetaR - teta0] = [0.] * workNum
        cumWrongs[tetaR - teta0] = [0.] * workNum
        # 50000 запуск теста, к ним считается число ошибок
        for eps in range(0, workNum):
            # result = [False, 0.]
            wrong = 0.
            obs = 0.
            for i in range(0, n + 1):
                result = fun2(var, tetaR, float(eps / steps))
                # result = Test1(teta0, teta1)
                obs += result[1]
                if not result[0]:
                    wrong += 1
            wrongs[tetaR - teta0][eps] = wrong
            observations[tetaR - teta0][eps] = obs
            cumObs += obs
            cumWrong += wrong
            cumObservations[tetaR - teta0][eps] = cumObs
            cumWrongs[tetaR - teta0][eps] = cumWrong
            # print("При eps = " + str(eps / steps) + "\t wrong = " + str(wrong))
            # +"\tres[0] = "+str(result[0])+"\tobs = "+str(result[1]))
        minW = min(wrongs[tetaR - teta0])
        maxW = max(wrongs[tetaR - teta0])
        avgW = stats.mean(wrongs[tetaR - teta0])
        minO = min(observations[tetaR - teta0])
        maxO = max(observations[tetaR - teta0])
        avgO = stats.mean(observations[tetaR - teta0])

        # for t in range(10):
        #     print(wrongs[tetaR - teta0][t*5:(t+1)*5])

        # print("eps = "+str(eps / steps)+"\tmin wrong = "+str(minW))
        write_res("task #"+str(var), tetaR, minO, minW, maxO, maxW, avgO, avgW)
        print("\nПри teta = " + str(tetaR))
        print("min obs = " + str(minO) + "\nmin wrong = " + str(minW))
        print("max obs = " + str(maxO) + "\nmax wrong = " + str(maxW))
        print("\navg obs = " + str(avgO) + "\navg wrong = " + str(avgW))

    return observations, wrongs, cumObservations, cumWrongs


def write_res(task, tetaR, minO, minW, maxO, maxW, avgO, avgW):

    f.write(task)
    f.write("\nПри teta = " + str(tetaR))
    f.write("\nmin obs = " + str(minO) + "\nmin wrong = " + str(minW))
    f.write("\nmax obs = " + str(maxO) + "\nmax wrong = " + str(maxW))
    f.write("\navg obs = " + str(avgO) + "\navg wrong = " + str(avgW))
    f.write("\n\n")


r1_ = 30
r2_ = 170


def f1():
    print("\n****Верна первая гипотеза****\n")
    res = test(0)
    drawplot(res[0], [45, 80], 'наблюдения H0')
    drawplot(res[0], [r1_, 170], 'наблюдения H0_')
    drawplot(res[1], [25, -15], 'ошибки первого рода')
    drawplot(res[1], [r1_, 195], 'ошибки первого рода_')

    drawplot(res[2], [25, -15], 'накопленные наблюдения H0')
    drawplot(res[3], [25, 170], 'накопленные ошибки первого рода')
    # res(wrongs0, observations0, "t1_0")


def f2():
    print("\n****Верна вторая гипотеза****\n")
    res = test(1)
    drawplot(res[0], [25, -5], 'наблюдения H1')
    drawplot(res[0], [r1_, 195], 'наблюдения H1_')
    drawplot(res[1], [25, -25], 'ошибки второго рода')
    drawplot(res[1], [r1_, r2_], 'ошибки второго рода_')

    drawplot(res[2], [25, -15], 'накопленные наблюдения Н1')
    drawplot(res[3], [25, -25], 'накопленные ошибки второго рода')
    # res(wrongs1, observations1, "t1_1")


def f3():
    print("\n****Верна первая гипотеза****\n")
    res = test(2)
    drawplot(res[1], [35, 5], 't2 ошибки первого рода')
    drawplot(res[1], [r1_, 170], 't2 ошибки первого рода_')
    drawplot(res[0], [35, 5], 't2 наблюдения H0')
    drawplot(res[0], [r1_, 170], 't2 наблюдения H0_')

    drawplot(res[2], [25, -15], 't2 накопленные наблюдения H0')
    drawplot(res[3], [25, -15], 't2 накопленные ошибки первого рода')
    # res(wrongs2, observations2, "t2_0")


def f4():
    print("\n****Верна вторая гипотеза****\n")
    res = test(3)
    drawplot(res[1], [35, 5], 't2 ошибки второго рода')
    drawplot(res[1], [r1_, 170], 't2 ошибки второго рода_')
    drawplot(res[0], [35, 5], 't2 наблюдения H1')
    drawplot(res[0], [r1_, 170], 't2 наблюдения H1_')

    drawplot(res[2], [25, -45], 't2 накопленные наблюдения H1')
    drawplot(res[3], [25, -15], 't2 накопленные ошибки второго рода')
    # res(wrongs3, observations3, "t2_1")


def second():
    print("\n************ПУНКТ 1************\n")
    f1()
    f2()
    print("\n************ПУНКТ 2************\n")
    f3()
    f4()


def corrupt(hyp, eps, tetaR):
    return round(float((1 - eps) * hyp + eps * np.random.poisson(tetaR)), 5)


logB = math.log(B)
logA = math.log(A)


def fun2(scenario, tetaR, eps):
    global A
    global B
    global logA
    global logB
    global teta0
    global teta1

    tetaW = teta0 if scenario % 2 == 0 else teta1
    accept = False  # True if scenario % 2 == 0 else

    number = 0
    sumZ = 0
    values = []
    Zs = []

    while True:
        t = 0.
        picker = np.random.uniform(0, 1)

        if picker <= eps:
            if scenario < 2:
                t = np.random.poisson(tetaR)
            else:
                t = tetaR
        else:
            t = np.random.poisson(tetaW)
        # t = np.random.poisson(tetaW)
        values.append(t)
        Zs.append(calcZ(t, teta0, teta1))
        sumZ += Zs[-1]

        if scenario % 2 == 0:
            if sumZ >= logA:
                accept = True  # отколняем H0
                break
            if sumZ <= logB:
                accept = False  # принимаем H0
                break
            if logB < sumZ < logA:
                number += 1
        elif scenario % 2 == 1:
            if sumZ >= logA:
                accept = False  # принимаем H1
                break
            if sumZ <= logB:
                accept = True  # отклоняем H1
                break
            if logB < sumZ < logA:
                number += 1

    return [accept, number]


def Test0(teta0, teta1):
    sumZ = 0
    accept = False
    global A
    global B
    number = 0
    values = []
    Zs = []
    while True:
        k = np.random.poisson(teta0)
        values.append(k)
        Zs.append(calcZ(k, teta0, teta1))
        sumZ += Zs[-1]
        if sumZ >= math.log(A):
            accept = True  # принимаем H0
            break
        if sumZ <= math.log(B):
            accept = False  # отклоняем H0
            break
        if math.log(B) < sumZ < math.log(A):
            number += 1
    return [accept, number]


def Test1(teta0, teta1):
    sumZ = 0
    accept = False
    global A
    global B
    number = 0
    values = []
    Zs = []
    while True:
        k = np.random.poisson(teta1)
        Zs.append(calcZ(k, teta0, teta1))
        sumZ += Zs[-1]
        if sumZ >= math.log(A):
            accept = True  # принимаем H1
            break
        if sumZ <= math.log(B):
            accept = False  # отклоняем H1
            break
        if math.log(B) < sumZ < math.log(A):
            number += 1
    return [accept, number]


# first(1)
start_time = time.time()
# print(fun2(at, bt, 1, 65, float(0.1 / steps)))
print("Входные:")
print("H0 = " + str(teta0))
print("H1 = " + str(teta1))
print("a = " + str(a))
print("b = " + str(b))
print("шагов: " + str(steps))

f = open("results.txt", 'w')

second()

f.close()
print("--- %s seconds ---" % (time.time() - start_time))
# print(np.linspace(0,1,21))
# np.random.seed(123)
#
# x = np.random.randint(-5, 5, 40)
# y = np.random.randint(0, 10, 40)
# z = np.random.randint(-5, 5, 40)
# s = np.random.randint(10, 100, 40)
#
# fig = plt.figure()
# ax = fig.add_subplot(111, projection='3d')
# ax.scatter(x, y, z, s=s)
# plt.show()
