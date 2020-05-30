# HashGraph
An optimized generic Graph Container
<br>
 This graph utilizes unordered_maps to store vertices with its key in an unordered_map as well as storing edges in
 another unordered_map with a key pair denoting the vertices of the edges as the key.
 <br>
 <br>
 <strong>Functions supported:</strong><br> 
 Elementary Circuit Finding Algorithm as per Donald B. Johnson method<a href = "https://www.cs.tufts.edu/comp/150GA/homeworks/hw1/Johnson%2075.PDF">*</a><br>
  Depth First Traversal Algorithm<br> 
  Breadth First Traversal Algorithm<br> 
  <br>
  This graph implementation uses unordered_maps which would cause slow downs due to unfriendly cache behaviour. However,
  this graph implementation was intended for internally storing objects like a container while also providing graph 
  functions such as adding edges and traversing said graph (refer to the supported functions section). Thus to aid in
  alleviating such unfriendly cache behaviour for the use case intended for the implementation, it might be recommended
  to store graph edges externally in a contiguous container and provide this container to pointers to these edges.
  <br>
  <br>
  For proper use, a user may inherit both the edge and vertex classes into his own link and node classes and use 
  the graph functions seamlessly.
  