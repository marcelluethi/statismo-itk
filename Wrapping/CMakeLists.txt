
FIND_PACKAGE(WrapITK REQUIRED)
 
SET(WRAPPER_ITK_MODULE_DIR ${ITK_DIR}/WrapITK/Configuration/Typedefs)

include_directories(${WRAPPER_ITK_MODEL_DIR}  ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/statismo_ITK
					${STATISMO_INCLUDE_DIRS}
					${ITK_INCLUDE_DIRS}  ${PROJECT_SOURCE_DIR}/Representers
					${HDF5_INCLUDE_DIR} ${HDF5_INCLUDE_DIR_CPP})
link_directories(${ITK_LIBRARY_DIRS} ${STATISMO_LIBRARY_DIR} ${HDF5_LIBRARY_DIR} )

itk_wrap_module("statismo_ITK") # name of python package
	SET(WRAPPER_LIBRARY_DEPENDS ITKCommon ITKTransform ITKPyBase ITKIOImageBase ITKSpatialObjects ITKReview ITKMesh)
itk_auto_load_submodules() # includes all *.wrap custom files
itk_end_wrap_module()

