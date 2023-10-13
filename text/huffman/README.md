# The Huffman Coding Algorithm

This algorithm is based on the following observations regarding 
optimum prefix codes:
- A symbol that occurs more frequently will have shorter 
codewords than symbols that occur less frequently.
- The two symbols that occur least frequently will have 
codewords of the same length.
- In the tree corresponding to the optimum code, there must 
be two branches stemming from each intermediate node.
- If the final and whole Huffman tree was optimal for the whhole 
alphabet, then the reduced sub-tree is optimal for the reduced 
alphabet.

To obtain Huffman code with minimum variance, we always put the combined letter high up in the list.
