/*
 * This file is part of the statismo library.
 *
 * Author: Marcel Luethi (marcel.luethi@unibas.ch)
 *
 * Copyright (c) 2011 University of Basel
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the project's author nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 * TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifndef ITKVECTORIMAGE_REPRESENTER_BASE_H_
#define ITKVECTORIMAGE_REPRESENTER_BASE_H_

#include "statismo/Representer.h"
#include "itkImage.h"
#include "statismo_ITK/statismoITKConfig.h"
#include "statismo/CommonTypes.h"
#include "itkObject.h"



namespace statismo {
template <>
struct RepresenterTraits<itk::Image<itk::Vector<float, 3u>, 3u> > {

    typedef itk::Image<itk::Vector<float, 3u>, 3u>  VectorImageType;

	typedef VectorImageType::Pointer DatasetPointerType;
	typedef VectorImageType::Pointer DatasetConstPointerType;

	typedef typename VectorImageType::PointType PointType;
	typedef typename VectorImageType::PixelType ValueType;

	static void DeleteDataset(DatasetPointerType d) {
		// trick to delete pointers, which cannot be deleted directly,
		// as destructor is private
		VectorImageType::Pointer smartPointerD = d;;
	};
    ///@}

};


template <>
struct RepresenterTraits<itk::Image<itk::Vector<float, 2u>, 2u> > {

    typedef itk::Image<itk::Vector<float, 2u>, 2u>  VectorImageType;

	typedef VectorImageType::Pointer DatasetPointerType;
	typedef VectorImageType::Pointer DatasetConstPointerType;

	typedef typename VectorImageType::PointType PointType;
	typedef typename VectorImageType::PixelType ValueType;

	static void DeleteDataset(DatasetPointerType d) {};
    ///@}

};

}

namespace itk {

/**
 *  \ingroup Representers
 * \brief Base class for all Representers representing itk Vector images
 * \sa Representer
 */

template <class TPixel, unsigned ImageDimension, unsigned VectorDimension>
class VectorImageRepresenterBase : public Object, public statismo::Representer<itk::Image<itk::Vector<TPixel, VectorDimension>, ImageDimension > >  {
public:

	/* Standard class typedefs. */
	typedef VectorImageRepresenterBase            Self;
//	typedef Object	Superclass;
//	typedef SmartPointer<Self>                Pointer;
//	typedef SmartPointer<const Self>          ConstPointer;



	/** Run-time type information (and related methods). */
	//itkTypeMacro( VectorImageRepresenterBase );
    
    typedef itk::Image<itk::Vector<TPixel, VectorDimension>, ImageDimension> ImageType;

	/// The type of the data set to be used

	typedef typename statismo::Representer<ImageType > RepresenterBaseType;
	typedef typename RepresenterBaseType::DomainType DomainType;
	typedef typename RepresenterBaseType::PointType PointType;
	typedef typename RepresenterBaseType::ValueType ValueType;
	typedef typename RepresenterBaseType::DatasetType DatasetType;
	typedef typename RepresenterBaseType::DatasetPointerType DatasetPointerType;
	typedef typename RepresenterBaseType::DatasetConstPointerType DatasetConstPointerType;

	void CloneBaseMembers(VectorImageRepresenterBase* clone) const;
	void LoadBaseMembers(const H5::CommonFG& fg);

	/** Set the reference that is used to build the model */
	virtual void SetReference(DatasetPointerType ds);
	virtual DatasetConstPointerType GetReference() const { return m_reference; }

	virtual const DomainType& GetDomain() const { return m_domain; }

	virtual void Save(const H5::CommonFG& fg) const;
	virtual unsigned GetNumberOfPoints() const;
	virtual unsigned GetPointIdForPoint(const PointType& point) const;
            

	virtual unsigned GetDimensions() const { 	return ImageType::ImageDimension; }

    static void DeleteDataset(DatasetPointerType ds) {}// do nothing, as we are working with smart pointers

	statismo::VectorType PointToVector(const PointType& pt) const;


	/**
	 * Creates a sample by first aligning the dataset ds to the reference using Procrustes
	 * Alignment.
	 */
	virtual statismo::VectorType SampleToSampleVector(DatasetConstPointerType ds) const;
	virtual DatasetPointerType SampleVectorToSample(const statismo::VectorType& sample) const;

	ValueType PointSampleFromSample(DatasetConstPointerType sample, unsigned ptid) const;
	virtual ValueType PointSampleVectorToPointSample(const statismo::VectorType& pointSample) const;
	virtual statismo::VectorType PointSampleToPointSampleVector(const ValueType& v) const;


protected:

    /**
     * Read/write/create DataSets
     */
    static DatasetPointerType ReadDataset(const char* filename);
    static void WriteDataset(const char* filename, const ImageType* image);


	VectorImageRepresenterBase();
	virtual ~VectorImageRepresenterBase();

	DatasetConstPointerType m_reference;
	DomainType m_domain;
};

} // namespace itk

#include "itkVectorImageRepresenterBase.txx"

#endif /* itkVectorImageRepresenter_H_ */
