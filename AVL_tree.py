# 2018-10-11

# Adelson, Velskii, Landisから命名
# AST木: 木の各nodeに高さを定め、任意のnodeの高度差が-1, 0, 1

#########################################################################
# 未完　p.143 removeメソッドとremoveFromParentメソッドが未定義
#########################################################################


class BinaryNode:
    def __init__(self, value=None):
        self.value = value
        self.left = None
        self.right = None
        self.height = 0

    def computeHeight(self):
        # leafの高さ = 0, not leafの高さ = (2つのnodeの高さの最大値) + 1,
        # 存在しない子nodeの高さ = -1
        height = -1
        if self.left:
            height = max(height, self.left.height)
        if self.right:
            height = max(height, self.right.height)

        self.height = height + 1

    def heightDifference(self):
        leftTarget = 0
        rightTarget = 0
        if self.left:
            leftTarget = 1 + self.left.height
        if self.right:
            rightTarget = 1 + self.right.height
        return leftTarget - rightTarget

    def add(self, val):
        newRoot = self
        if val <= self.value:
            self.left = self.addToSubTree(self.left, val)
            if self.heightDifference() == 2:
                if val <= self.left.value:
                    newRoot = self.rotateRight()
                else:
                    newRoot = self.rotateLeftRight()
        else:
            self.right = self.addToSubTree(self.right, val)
            if self.heightDifference() == -2:
                if val > self.right.value:
                    newRoot = self.rotateLeft()
                else:
                    newRoot = self.rotateRightLeft()

        newRoot.computeHeight()
        return newRoot

    def addToSubTree(self, parent, val):
        if parent is None:
            return BinaryNode(val)

        parent = parent.add(val)
        return parent

    def rotateRight(self):
        newRoot = self.left
        grandson = newRoot.right
        self.left = grandson
        newRoot.right = self

        self.computeHeight()
        return newRoot

    def rotateRightLeft(self):
        child = self.right
        newRoot = child.left
        grand1 = newRoot.left
        grand2 = newRoot.right
        child.left = grand2
        self.right = grand1

        newRoot.left = self
        newRoot.right = child

        child.computeHeight()
        self.computeHeight()
        return newRoot

    def rotateLeft(self):
        newRoot = self.right
        grandson = newRoot.left
        self.right = grandson
        newRoot.left = self

        self.computeHeight()
        return newRoot

    def rotateLeftRight(self):
        child = self.left
        newRoot = child.right
        grand1 = newRoot.left
        grand2 = newRoot.right
        child.right = grand2
        self.left = grand1

        newRoot.left = child
        newRoot.right = self

        child.computeHeight()
        self.computeHeight()
        return newRoot


class BinaryTree:
    def __init__(self):
        self.root = None

    def add(self, value):
        if self.root is None:
            self.root = BinaryNode(value)
        else:
            self.root.add(value)

    def __contains__(self, value):
        currentNode = self.root
        while currentNode:
            if value < currentNode.value:
                currentNode = currentNode.left
            elif currentNode.value < value:
                currentNode = currentNode.right
            else
                return True

        return False
