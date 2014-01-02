#
# This file is part of the statismo library.
#
# Author: Marcel Luethi (marcel.luethi@unibas.ch)
#
#Copyright (c) 2013 University of Basel
# All rights reserved.
#
#
# This example shows how samples can be drawn from a shape model, using the Python interface of statismo-itk.
#
import sys
import statismo_ITKPython as sitk
import os.path


def main(modelname, resdir): 

    rep = sitk.itkStandardMeshRepresenterF3.New()
    model = sitk.itkStatisticalModelMF3.New()
    model.Load(rep, modelname)

    mean = model.DrawMean()
    writer = sitk.itkMeshFileWriterMF3.New(mean, FileName=os.path.join(resdir, "mean.vtk"))
    writer.Update()
    

    for i in xrange(0, 10):
        sample = model.DrawSample()
        writer = sitk.itkMeshFileWriterMF3.New(sample, FileName=os.path.join(resdir, "sample-%d.vtk"%i))
        writer.Update()
        
    

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print "usage: %s model resultdir" 
        sys.exit(-1)

    main(*sys.argv[1:])
