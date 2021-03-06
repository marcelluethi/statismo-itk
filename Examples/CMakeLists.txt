CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(ssm_itk)
SET(CMAKE_VERBOSE_MAKEFILE ON)



IF(WIN32)
# Fix for VS2012 that has _VARIADIC_MAX set to 5. For some of the examples, this does not seem to be sufficient. 
#Don't set too high because it increases compiler memory usage / compile-time.
add_definitions( -D_VARIADIC_MAX=9 )
ENDIF()


   

FILE(GLOB INCLUDE_FILES *.h)
FILE(GLOB SOURCE_FILES  *.txx )

include_directories(${STATISMO_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/statismo_ITK ${CMAKE_SOURCE_DIR}/Representers   
					${HDF5_INCLUDE_DIR} ${HDF5_INCLUDE_DIR_CPP}  ${CMAKE_SOURCE_DIR}
					)

link_directories( ${ITK_LIBRARY_DIRS} ${STATISMO_LIBRARY_DIR} )

add_executable (itkBuildDeformationModel buildDeformationModel.cpp 
	${SOURCE_FILES}
	${INCLUDE_FILES}
) 
ADD_DEPENDENCIES(itkBuildDeformationModel HDF5)
target_link_libraries (itkBuildDeformationModel ${ITK_LIBRARIES})

add_executable (itkDeformationModelFitting deformationModelFitting.cpp 
	${SOURCE_FILES}
	${INCLUDE_FILES}
) 
ADD_DEPENDENCIES(itkDeformationModelFitting HDF5)
target_link_libraries (itkDeformationModelFitting   ${ITK_LIBRARIES} )

add_executable (itkBuildShapeModel buildShapeModel.cpp 
	${SOURCE_FILES}
	${INCLUDE_FILES}
) 
ADD_DEPENDENCIES(itkBuildShapeModel HDF5)
target_link_libraries (itkBuildShapeModel ${ITK_LIBRARIES} )

add_executable (itkBuildShapeModel_75pcvar buildShapeModel_75pcvar.cpp 
	${SOURCE_FILES}
	${INCLUDE_FILES}
) 
ADD_DEPENDENCIES(itkBuildShapeModel_75pcvar HDF5)
target_link_libraries (itkBuildShapeModel_75pcvar ${ITK_LIBRARIES} )

add_executable (itkBuildGaussianProcessDeformationModel buildGaussianProcessDeformationModel.cpp 
	${SOURCE_FILES}
	${INCLUDE_FILES}
) 
ADD_DEPENDENCIES(itkBuildGaussianProcessDeformationModel HDF5)
target_link_libraries (itkBuildGaussianProcessDeformationModel ${ITK_LIBRARIES} )




add_executable (itkShapeModelFitting shapeModelFitting.cpp 
	${SOURCE_FILES}
	${INCLUDE_FILES}
) 
ADD_DEPENDENCIES(itkShapeModelFitting HDF5)
target_link_libraries (itkShapeModelFitting  ${ITK_LIBRARIES})

add_executable (itkLandmarkConstrainedShapeModelFitting landmarkConstrainedShapeModelFitting.cpp 
	${SOURCE_FILES}
	${INCLUDE_FILES}
) 
ADD_DEPENDENCIES(itkLandmarkConstrainedShapeModelFitting HDF5)
target_link_libraries (itkLandmarkConstrainedShapeModelFitting  ${ITK_LIBRARIES})




add_executable(itkLowRankGaussianProcessImageToImageRegistration lowRankGaussianProcessImageToImageRegistration.cpp
        ${SOURCE_FILES}
        ${INCLUDE_FILES}
) 
ADD_DEPENDENCIES(itkLowRankGaussianProcessImageToImageRegistration HDF5)
target_link_libraries (itkLowRankGaussianProcessImageToImageRegistration  ${ITK_LIBRARIES})

add_executable(itkSimpleGaussianProcessImageToImageRegistration simpleGaussianProcessImageToImageRegistration.cpp
        ${SOURCE_FILES}
        ${INCLUDE_FILES}
) 
ADD_DEPENDENCIES(itkSimpleGaussianProcessImageToImageRegistration HDF5)
target_link_libraries (itkSimpleGaussianProcessImageToImageRegistration  ${ITK_LIBRARIES})



INSTALL(TARGETS 
itkBuildDeformationModel  
itkDeformationModelFitting 
itkBuildShapeModel 
itkBuildShapeModel_75pcvar 
itkShapeModelFitting 
itkLandmarkConstrainedShapeModelFitting 
itkBuildGaussianProcessDeformationModel
itkLowRankGaussianProcessImageToImageRegistration
itkSimpleGaussianProcessImageToImageRegistration
RUNTIME DESTINATION bin)
INSTALL(PROGRAMS runITKExamples.sh DESTINATION  bin)
