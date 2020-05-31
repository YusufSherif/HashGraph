# HashGraph
An optimized generic Graph Container
<br>
 This graph utilizes unordered_maps to store vertices with its key in an unordered_map as well as storing edges in
 another unordered_map with a key pair denoting the vertices of the edges as the key. This is a generic directed, 
 unweighted graph implementation; however, it is flexible enough to hold any vertex or edge type so that it may be 
 used to contain any class type of edge or any class type of vertex with the appropriate key. Therefore, it could be used
 to mimic weighted graphs by using a std::pair of edge type and a weight type as the EDGE template type.
 <br>
 <br>
 <strong>Functions supported:</strong><br> 
 Elementary Circuit Finding Algorithm as per Donald B. Johnson method
 <a href = "https://www.cs.tufts.edu/comp/150GA/homeworks/hw1/Johnson%2075.PDF">*</a><br>
  Depth First Traversal Algorithm<br> 
  Breadth First Traversal Algorithm<br> 
 <br>
  