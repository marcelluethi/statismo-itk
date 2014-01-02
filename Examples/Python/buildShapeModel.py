#
# This file is part of the statismo library.
#
# Author: Marcel Luethi (marcel.luethi@unibas.ch)
#
#Copyright (c) 2013 University of Basel
# All rights reserved.
#
#
# This example shows how a shape model can be built using statismo_ITK's python wrapping
#
import sys
import statismo_ITKPython as sitk
import os.path
import os


def readMesh(meshFn):
	meshReader = sitk.itkMeshFileReaderMF3.New(FileName=meshFn)
	meshReader.Update()
	return meshReader.GetOutput()


def main(datadir, modelFilename): 

	meshFilenames = [f for f in os.listdir(datadir) if f.endswith('.vtk')]  
	if len(meshFilenames) == 0:
		println("no valid vtk files found in directory, exiting")
		sys.exit(-1)
	

	rep = sitk.itkStandardMeshRepresenterF3.New()
	referenceMesh = readMesh(os.path.join(datadir, meshFilenames[0]))
	rep.SetReference(referenceMesh)

	dataManager = sitk.itkDataManagerMF3.New()
	dataManager.SetRepresenter(rep)
	
	for meshFn in meshFilenames:
		fullMeshPath = os.path.join(datadir, meshFn)
		mesh = readMesh(fullMeshPath)
 		dataManager.AddDataset(mesh, fullMeshPath)

 	modelBuilder = sitk.itkPCAModelBuilderMF3.New()
 	model = modelBuilder.BuildNewModel(dataManager.GetData(), 0.1) 	
			
	model.Save(modelFilename)
	print("successfully created model")             
    

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print "usage: %s datadir shapemodel" 
        sys.exit(-1)

    main(*sys.argv[1:])
