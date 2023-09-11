# Recovery 3D: a tool for mesh reconstruction and tetrahedral surface decomposition 


OpenGL GUI Tool to compute delaunay tetrahedra, 3d voronoi space partitioning and reconstruct a 3d mesh from a point cloud

<a href="url"><img src="https://github.com/alicata/r3d-2001/blob/master/docs/img/r3d_tool.png" align="center" height="300" width="500" ></a>

# Getting Started
For a quick feel of the tool launch the OpenGL GUI app and choose to import the in-memory rabbit from the File Menu and then start one of the reconstruction methods (Voronoi, or 3D Surface, etc...) from the Reconstruction Menu 

# Overview 
This research thesis project is about three-dimensional surface estimation from 3-d point clouds. This type of data is naturally produced in a varieties of engineering applications. For example, range laser scanners generate depth information from a physical object (range image) and the result is a partial set of three-dimensional surface points. Range images from different view angles are then aligned and merged into a single point cloud. The problem is then to recover a polygonal mesh from such points. 

<a href="url"><img src="https://github.com/alicata/r3d-2001/blob/master/docs/img/justvoronoi.png" align="center" height="200" width="200" ></a>

The core of the surface reconstructor is a combination of three algorihtms: Crust, Delaunay tetrahedralization, and Voronoi tessellation. The reconstuction application reads in point cloud data and produce a reconstructed three-dimensional polygonal mesh. 

<a href="url"><img src="https://github.com/alicata/r3d-2001/blob/master/docs/img/pole_ins1.png" align="center" height="200" width="440" ></a>

The Crust algorithm is built from 3D Medial Axis transform and pole finding algorithm. 


# Thesis
Topological 3-D Reconstruction from Point Sets by Space Tetrahedralization

## Abstract
**3-D Topological Reconstruction** is the reverse engineering problem of recovering the 3-dimensional shape of a cloud of points (these points are usually generated from a 3-d laser scanner ). For example, a human being could be scanned and his 3-d surface reconstructed by the software for applications such as Rapid Prototyping, 3-d medical imaging, and 3-d online shopping. This undergraduate final thesis project investigates the algorithms, and the technology needed to design and develop a prototype C/C++ software application capable of such shape recovery task.

**keywords**: reverse engineering, computational geometry, surface reconstruction, Voronoi diagrams, tetrahedralizer.

### Acknowledgements
Project Author: Aaron Licata<br> 
Project Supervisors: Dr Paul Phillips, Dr Stuart Pattinson<br>
Cavendish School of Computer Science<br>
University of Westminster<br>
115 New Cavendish Street , London, United Kingdom<br>
 



## 3-D Surface Reconstruction by Tetrahedralization
The project investigates the geometric mechanisms of Topological Reconstruction by Space Tetrahedralization . The followed method is based on 3-d Voronoi cell decomposition of space occupied by a point set, and exploitation of such computed space structure to infer topological information about neighbouring points in the set.
Voronoi tessellation, Delunay tetrahedralization, and Medial Axis transform are the building blocks of the higher-level surface boundary estimation algorithm.


## Topological Reconstruction from Point Sets and Tetrahedral Space Decomposition: Introduction
This research thesis project is about three-dimensional surface estimation from 3-d point clouds. This type of data is naturally produced in a varieties of engineering applications. For example, range laser scanners generate depth information from a physical object (range image) and the result is a partial set of three-dimensional surface points. Range images from different view angles are then aligned and merged into a single point cloud. The problem is then, how to recover a polygonal mesh from such points?

There are several approaches to surface reconstruction: distance function methods, direct triangulation methods, alpha-shape methods. The approach used here is direct triangulation and with refinement steps because what is sought is interpolation of sampled data rather than approximation (regardeless of overall surface estimation errors).

The core of the surface reconstructor is a combination of three algorihtms: crust, Delaunay tetrahedralization, and Voronoi tessellation. The final reconstuction application should be able to read in point cloud data and produce a reconstructed three-dimensional polygonal mesh. It should also be able to handle numerical problems and deliver acceptable rubustness. 

## Delaunay Tetrahedralizer: A Simplicial Complex Builder
The tetrahadrilization is a first approximation to the original physical scanned surface. It is done implementing a number of functions as prescribed by Watson-Boyer algorithms.

A super tetrahedron is created first and all data points inserted into it one at a time. Any of the tetrahedra which are related to a just inserted point, are broken up into new tetrahedra. These new tetrahedra have the property that do not contain any insertion point. This rule, garantees that the centers of such tetrahedra are the voronoi vertices (used to refine the Delaunay approximation later on).

The 3-d Delaunay tetrahedralization is considerably harder, less intuitive and computationally more expensive than the 2-d Delaunay triangulation counterpart. These difficulty is partly decreased by using Boyer-Waston algorithm, wich extends to any dimensions.

### Interpretation of Watson-Boyer Algorithm

- Create Super Tetrahedron
- Add Super Tetrahedron To Global Tetrahedron List
- For Each Point of the Input Data Set
- Find And Delete Ball-Seeded Tetrahedra
- Place Doubly Occurring Faces in a Temporary Face List
- Retain Singly Occurring Faces
- For Each Singly Occurring Face
- Create a Tetrahedron Using Face and Current Point
- Add New Tetrahedron to Global Tetrahedron List
- Delete Arbitrary Boundary Tetra from Global Tetrahedron List
- The final tetrahedralization is a simplicial complex: an aggregate of tetrahedra whose outer boundary is the 3-d convex-hull of the point cloud.

### Voronoi Diagram in 3-Dimensional Space: A Space Tessellator

The Voronoi diagram in 3-d is visually considerably more complex then its counterpart in 2-dimensional space. However, like in 2-d, each sample point of the scanned surface is surrounded by a Voronoi 3-d cell. This Voronoi cell represents the space around the sample point closer to it than any other sample point. The Voronoi diagram in 3-d is a way of partitioning space in a 'fair' way.

A Voronoi 3-d cell is a polyhedron. Each Voronoi face lies on a plane, and each such plane separates exactly two sample points at equal distance.

The Voronoi diagram lies in a space that is said to be dual to the Delaunay tetrahedralization space. This theory of duality is not just aesthetically fascinating but has also some practical implications. Notably, it is much easier to compute the Delaunay tetrahedralization than the Voronoi diagram in 3-d. Since the two geometrical structures are dual, it is possible to calculate the Delaunay tetrahedralization and then convert it into the Voronoi diagram.

### Medial-Axis Transform
Next step is to perform the medial-axis transform on union of the Voronoi and Delaunay point sets. 

### Computation of the Crust
Extract crust from medial-axis and and pole finding. 

### Data Structures
There are three basic data structures acting as building blocks for the overall agorithmic system. Thetrahedron structure links to four Face3 objects, and each in turn links to Edge3 objects. Edge3 objects have two links to Vertex objects stored in a global vertex array.

## Prototype Software Downloads
The final prototype reconstructor software application allows topological reconstruction from static sparse data: givend a cloud of points, it is possible to reconstruct its 3-d shape, its convex-hull, and its Voronoi tessellation.


## Essential References:
N.Amenta, et al., A New Voronoi-Based Surface Reconstruction Algorithm. SIGGRAPH 98, 1998, 415-421. http://portal.acm.org/citation.cfm?id=280814.280947&coll=GUIDE&dl=GUIDE&type=series&idx=280814&part=Proceedings&WantType=Proceedings&title=International%20Conference%20on%20Computer%20Graphics%20and%20Interactive%20Techniques&CFID=73066033&CFTOKEN=75331022

A. Bowyer, Computing Dirichlet tessellations, The Computer Journal, 24(2):162-166, 1981. http://comjnl.oxfordjournals.org/cgi/content/short/24/2/162 

D. Watson, Computing the n-dimensional Delaunay tessellation with application to Voronoi polytopes, The Computer Journal, 24(2):167-172, 1981. http://comjnl.oxfordjournals.org/cgi/content/abstract/24/2/167

### Other References
3D Scanners Ltd, World-Wide-Web, URL: http://www.3dscanners.com

K. Clarkson, Hull, World-Wide-Web, URL: http://cm.bell-labs.com/netlib/voronoi/hull.html

H. Hoppe, Surface Reconstruction from Unorganized Points. Ph.D. Thesis, Computer Science and Engineering, University of Washington , 1994

M.J. Laszlo, Computational Geometry And Computer Graphics, Prentice Hall, New Jersey , 1996

A. Licata, Project Recovery: A 3-D Surface Reconstructor, BSc (Hons) Final Project, Cavendish School of Computer Science, University of Westminster, London, UK, 2001

S. Pattinson,On-line Lecture Notes, Module 3MTS326 Graphics And Visualization, Dept. Mathematics, University of Westminster, 2000, World-Wide-Web, URL: http://intranet.cscs.wmin.ac.uk/~pattins/3mts326/mts326.html

F. Preparata, M. Shamos, Computational Geometry: An Introduction, Springer, New York , Second Edition, 1988

R. Shewchuck, Adaptive Precision Floating-Point Arithmetic and Fast Robust Predicates for Computational Geometry, World-Wide-Web, URL: http://www.cs.cmu.edu/~quake/robust.html


