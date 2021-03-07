class Trie:
    def __init__(self):
        self.root = Node()

    def insert(self, s):
        parent = self.root
        for i, c in enumerate(s):
            if c in parent.nexts:
                child = parent.nexts[c]
            else:
                child = Node()
                parent.nexts[c] = child

            if i == len(s)-1:
                child.is_end = True

            parent = child

    def search(self, s):
        node = self.root
        for c in s:
            if c not in node.nexts:
                return False
            node = node.nexts[c]

        return node.is_end

class Node:
    def __init__(self):
        self.is_end = False
        self.nexts = {}

def main():
    strs = ["the", "their", "there", "was", "when"]
    trie = Trie()
    for s in strs:
        trie.insert(s)

    print(trie.search("the"))
    print(trie.search("thei"))
    print(trie.search("their"))
    print(trie.search("theirr"))

main()
