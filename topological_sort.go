package main

import (
    "fmt"
)

type Node struct {
    id int
    parents []*Node
    children []*Node
}

func newNode(id int) *Node {
    return &Node{
        id: id,
        parents: nil,
        children: nil,
    }
}

func (n *Node) setChildren(children []*Node) {
    n.children = children
    for _, node := range children {
        node.parents = append(node.parents, n)
    }
}

func (n *Node) removeChild(c *Node) {
    idx := 0
    for _, node := range n.children {
        if node.id == c.id {
            n.children = append(n.children[:idx], n.children[idx+1:]...)
            break
        }
        idx++
    }
}

func (n *Node) removeParent(p *Node) {
    idx := 0
    for _, node := range n.parents {
        if node.id == p.id {
            n.parents = append(n.parents[:idx], n.parents[idx+1:]...)
            break
        }
        idx++
    }
}

// [参考資料](https://ja.wikipedia.org/wiki/%E3%83%88%E3%83%9D%E3%83%AD%E3%82%B8%E3%82%AB%E3%83%AB%E3%82%BD%E3%83%BC%E3%83%88)
func top_sort(nodes []*Node) {
    res := []*Node{}

    nodesWithNoIncomeEdge := []*Node{}
    for _, node := range nodes {
        if len(node.parents) == 0 {
            nodesWithNoIncomeEdge = append(nodesWithNoIncomeEdge, node)
        }
    }

    for len(nodesWithNoIncomeEdge) > 0 {
        node := nodesWithNoIncomeEdge[0]
        nodesWithNoIncomeEdge = nodesWithNoIncomeEdge[1:]
        res = append(res, node)

        for _, child := range node.children {
            // node.removeChild(child)
            child.removeParent(node)
            if len(child.parents) == 0 {
                nodesWithNoIncomeEdge = append(nodesWithNoIncomeEdge, child)
            }
        }
    }

    for _, n := range res {
        fmt.Printf("%d ", n.id)
    }
    fmt.Println()
}

func p(node *Node) {
    fmt.Printf("id: %d\n", node.id)
    fmt.Printf("Parents: ")
    for _, n := range node.parents {
        fmt.Printf("%d ", n.id)
    }
    fmt.Printf("\n")

    fmt.Printf("Children: ")
    for _, n := range node.children {
        fmt.Printf("%d ", n.id)
    }
    fmt.Printf("\n")
}

func main() {
    n2 := newNode(2);
    n3 := newNode(3);
    n5 := newNode(5);
    n7 := newNode(7);
    n8 := newNode(8);
    n9 := newNode(9);
    n10 := newNode(10);
    n11 := newNode(11);

    n3.setChildren([]*Node{ n8, n10 })
    n5.setChildren([]*Node{ n11 })
    n7.setChildren([]*Node{ n8, n11 })
    n8.setChildren([]*Node{ n9 })
    n11.setChildren([]*Node{ n2, n9, n10 })

    nodes := []*Node { n2, n3, n5, n7, n8, n9, n10, n11 }
    top_sort(nodes)
}
