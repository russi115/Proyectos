const preOrder = (tree, nodeToFind) => {
    if (!tree) return false
    if (tree.node === nodeToFind) return []

    const leftPath = preOrder(tree.left, nodeToFind)
    const rigthPath = preOrder(tree.rigth, nodeToFind)

    if (leftPath) return [0].concat(leftPath)
    if (rigthPath) return [1].concat(rigthPath)
}
