# Recovery 3D: a tool for mesh reconstruction and tetrahedral surface decomposition 


GUI Tool to compute delaunay tetrahedra, 3d voronoi space partitioning and reconstruct a 3d mesh from a point cloud

<a href="url"><img src="https://github.com/alicata/r3d-2001/blob/master/docs/img/r3d_tool.png" align="center" height="300" width="500" ></a>

# Getting Started
For a quick feel of the tool launch the GUI app and choose to import the in-memory rabbit from the File Menu and then start one of the reconstruction methods (Voronoi, 3D Surface, etc...) from the Reconstruction Menu 

# Overview 
This research thesis project is about three-dimensional surface estimation from 3-d point clouds. This type of data is naturally produced in a varieties of engineering applications. For example, range laser scanners generate depth information from a physical object (range image) and the result is a partial set of three-dimensional surface points. Range images from different view angles are then aligned and merged into a single point cloud. The problem is then to recover a polygonal mesh from such points. 

<a href="url"><img src="https://github.com/alicata/r3d-2001/blob/master/docs/img/justvoronoi.png" align="center" height="200" width="200" ></a>

The core of the surface reconstructor is a combination of three algorihtms: Crust, Delaunay tetrahedralization, and Voronoi tessellation. The reconstuction application reads in point cloud data and produce a reconstructed three-dimensional polygonal mesh. 

<a href="url"><img src="https://github.com/alicata/r3d-2001/blob/master/docs/img/pole_ins1.png" align="center" height="200" width="440" ></a>

The Crust algorithm is built from 3D Medial Axis transform and pole finding algorithm. 



 
