class Node:
    def __init__(self, ID, children=None):
        self.ID = ID
        self.children = children

    def set_children(self, children):
        self.children = children

n2 = Node(2)
n3 = Node(3)
n5 = Node(5)
n7 = Node(7)
n8 = Node(8)
n9 = Node(9)
n10 = Node(10)
n11 = Node(11)

n7.set_children([n8, n11])
n5.set_children([n11])
n3.set_children([n8, n10])
n11.set_children([n2, n9, n10])
n8.set_children([n9])

# 入力辺を持たないすべてのノードの集合
nodes = [n3, n5, n7]

# トポロジカルソートした結果を格納するリスト
L = []

while len(nodes) > 0:
    node = nodes.pop()
    L.append(node)

