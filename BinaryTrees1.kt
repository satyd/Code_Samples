import java.io.BufferedReader
import java.io.File
import kotlin.collections.ArrayDeque
import kotlin.math.abs

class Node(var value: Int = 0, val lvl: Int = 1, var left: Node? = null, var right: Node? = null, var strVal : String? = null) {

    var height = 0

    init {
        if (lvl > height)
            height = lvl
    }

    fun add(num: Int) {
        if (num == this.value)
            return
        if (num >= this.value) {
            if (this.right != null) {
                this.right?.let { this.right?.add(num) }
            } else {
                this.right = Node(num, this.lvl + 1)
                if (this.lvl + 1 > height)
                    height = this.lvl + 1
            }
        } else {
            if (this.left != null) {
                this.left?.let { this.left?.add(num) }
            } else {
                this.left = Node(num, this.lvl + 1)
                if (this.lvl + 1 > height)
                    height = this.lvl + 1
            }
        }

    }

    fun add(str: String) {
        if (str == this.strVal)
            return
        if (str >= this.strVal.toString()) {
            if (this.right != null) {
                this.right?.let { this.right?.add(str) }
            } else {
                this.right = Node(strVal = str, lvl = this.lvl + 1)
                if (this.lvl + 1 > height)
                    height = this.lvl + 1
            }
        } else {
            if (this.left != null) {
                this.left?.let { this.left?.add(str) }
            } else {
                this.left = Node(strVal = str,lvl = this.lvl + 1)
                if (this.lvl + 1 > height)
                    height = this.lvl + 1
            }
        }

    }


    fun max(): Node {
        return if (this.right != null)
            this.right!!.max()
        else
            this
    }

    fun min(): Node {
        return if (this.left != null)
            this.left!!.min()
        else
            this
    }

    fun find(value: Int): Node? = when {
        this.value > value -> left?.find(value)
        this.value < value -> right?.find(value)
        else -> this
    }

    fun findParent(target: Int): Node? {
        if (this.value == target)
            return null
        return when {
            this.left != null && this.left!!.value == target -> {
                this
            }
            this.right != null && this.right!!.value == target -> {
                this
            }
            else -> {
                if (target >= this.value)
                    this.right?.findParent(target)
                else {
                    this.left?.findParent(target)
                }
            }
        }
    }

    fun removeSingleChildNode(parent: Node, child: Node) {
        parent.value = child.value
        parent.left = child.left
        parent.right = child.right
    }

    fun isLeaf(v: Node): Boolean {
        return (v.left == null && v.right == null)
    }

    fun isFork(v: Node): Boolean {
        return (v.left != null && v.right != null)
    }

    fun remove(target: Int) {
        when {
            target > this.value -> {
                if (!isLeaf(this.right!!)) {
                    this.right?.remove(target)
                } else if (this.right?.value ?: -1 == target) {
                    this.right = null
                }

            }
            target < this.value -> {
                if (!isLeaf(this.left!!)) //if not leaf
                    this.left?.remove(target)
                else if (this.left?.value ?: -1 == target) {
                    this.left = null
                }
            }
            else -> {
                when {
                    this.left == null && this.right != null -> {
                        removeSingleChildNode(this, this.right!!)
                    }
                    this.right == null && this.left != null -> {
                        removeSingleChildNode(this, this.left!!)
                    }
                    this.right != null && this.left != null -> {
                        val next = this.right!!.min()
                        val parent = this.findParent(next.value)

                        if (next == parent!!.left) {
                            parent.left = next.right
                        } else if (next == parent.right) {//only if parent.value == toRemove
                            parent.right = null
                        }
                        this.value = next.value
                        //remove(this.right!!, next.value)
                    }
                    else -> {
                        print("wtf")
                    }
                }
            }
        }
    }

    fun ascending(rule: (v: Node) -> Boolean) {
        if (this.left != null)
            this.left!!.ascending(rule)

        if (rule(this))
            println("${this.value} ")

        if (this.right != null)
            this.right!!.ascending(rule)

    }

    fun ascending() {
        if (this.left != null)
            this.left!!.ascending()

        println("${this.value}")

        if (this.right != null)
            this.right!!.ascending()
    }

    fun depth(): Int {
        return kotlin.math.max((this.left?.depth() ?: -1), (this.right?.depth() ?: -1)) + 1
    }
    fun amount(): Int {
        return (this.left?.amount() ?: 0) + (this.right?.amount() ?: 0) + 1
    }

    fun balanced(): Boolean {

        //if(!this.isBalanced())
        //println("${this.value} ${this.left?.height} ${this.right?.height}")
        //println("${this.value} ${this.right?.depth()} ${this.left?.depth()}")
        return this.left?.balanced()?:true && this.right?.balanced()?:true && (abs((this.right?.depth() ?: -1) - (this.left?.depth() ?: -1)) <= 1)

    }

    fun children() : Int{
        //println("${this.value} ${this.left?.amount()} ${this.right?.amount()}")
        return (this.left?.children()?:0) + (this.right?.children()?:0) + (this.right?.amount() ?: 0) + (this.left?.amount() ?: 0)
    }
    fun ascendingChildren() {
        if (this.left != null)
            this.left!!.ascendingChildren()

        println("${this.value} ${(this.left?.amount()?:0) + (this.right?.amount()?:0)}")

        if (this.right != null)
            this.right!!.ascendingChildren()
    }

    fun printTree(root: Node) {
        val q = ArrayDeque<Pair<Node, Int>>(0)
        q.addLast(Pair(root, 0))
        while (!q.isEmpty()) {
            val curr = q.first()
            val node = curr.first
            val lvl = curr.second
            q.removeFirst()
            if (node.left != null)
                q.addLast(Pair(node.left!!, lvl + 1))
            if (node.right != null)
                q.addLast(Pair(node.right!!, lvl + 1))
            repeat(height - lvl)
            {
                print(" ")
            }
            print("${node.value} ")
            if (q.isEmpty() || q.first().second > lvl)
                println()
        }
    }
}

//fun secondMaxByRef(btree: Node) {
//    if (btree.removeBad(btree, btree.max()) == null) {
//        //btree.printTree(btree)
//        println("${btree.max().value}")
//    } else {
//        if (btree.left != null) {
//            println("${btree.left!!.max().value}")
//        } else {
//            println(0)
//        }
//    }
//}
//
fun secondMaxByValue(btree: Node) {
    btree.remove(btree.max().value)
    println(btree.max().value)
}

fun isLeaf(v: Node): Boolean {
    return (v.left == null && v.right == null)
}

fun isFork(v: Node): Boolean {
    return (v.left != null && v.right != null)
}

fun isBrunch(v: Node): Boolean {
    return (!isFork(v) && !isLeaf(v))
}

fun readArr(): IntArray {
    //val tree = Tree
    val br = File("input.txt").bufferedReader()
    //val str = readLine()!!.split(" ")
    val str = br.readLine().split(" ")
    return str.map { it.toInt() }.toTypedArray().toIntArray()

}

fun readLines(num:Int, br:BufferedReader):ArrayList<Pair<String,String>>{
    val res = ArrayList<Pair<String,String>>()
    repeat(num- 1){
        val r = br.readLine().replace("\n", "").split(" ")
        res.add(Pair(r[0],r[1]))
    }
    return res
}

fun findRoot(str : ArrayList<Pair<String,String>>){
    //
}

fun main() {
    val arr = readArr()

    val br = File("input.txt").bufferedReader()
    val num = br.readLine().toInt()
    val strings = readLines(num, br)
    val btree: Node?

//    repeat(num - 1){
//
//    }
    if (arr[0] != 0)
        btree = Node(arr[0])
    else
        btree = Node(0, 0)
    for (i in 1 until arr.size - 1) {
        if (arr[i] == 0)
            break
        btree.add(arr[i])
    }

    //btree.printTree(btree)
//    if(btree.balanced())
//        print("YES")
//    else
//        print("NO")
    //print(btree.children())
    //btree.ascendingChildren()
    //btree.ascending(::isLeaf)
    //btree.ascending(::isFork)
    //btree.ascending(::isBrunch)

    //secondMaxByValue(btree)
}