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


#ifndef ITKMODELBUILDER_H_
#define ITKMODELBUILDER_H_

#include "itkObject.h"
#include "itkObjectFactory.h"

#include "statismoITKConfig.h"
#include "itkDataManager.h"
#include "itkStatisticalModel.h"
#include "statismo/PCAModelBuilder.h"

namespace itk
{

/**
 * \brief ITK Wrapper for the statismo::PCAModelBuilder class.
 * \see statismo::PCAModelBuilder for detailed documentation.
 */
template <class T>
class PCAModelBuilder : public Object {
public:

	typedef PCAModelBuilder            Self;
	typedef Object	Superclass;
	typedef SmartPointer<Self>                Pointer;
	typedef SmartPointer<const Self>          ConstPointer;

	itkNewMacro( Self );
	itkTypeMacro( PCAModelBuilder, Object );


	typedef statismo::PCAModelBuilder<T> ImplType;
	typedef DataManager<T> DataManagerType;
	typedef typename DataManagerType::DataItemContainerType DataItemContainerType;

	PCAModelBuilder() : m_impl(ImplType::Create()){}

	virtual ~PCAModelBuilder() {
		if (m_impl) {
			delete m_impl;
			m_impl = 0;
		}
	}

	template <class F>
	typename std::tr1::result_of<F()>::type callstatismoImpl(F f) const {
		try {
			  return f();
		}
		 catch (statismo::StatisticalModelException& s) {
			itkExceptionMacro(<< s.what());
		}
	}



	typename StatisticalModel<T>::Pointer BuildNewModel(const DataItemContainerType* dataItems, float noiseVariance, bool computeScores = true) {


		// copy the itk data item types to standard data item
		typedef typename statismo::DataManager<T>::DataItemListType StatismoDataItemListType;

		StatismoDataItemListType dataItemsStatismo;
		for (unsigned i = 0; i < dataItems->Size(); i++) {
			dataItemsStatismo.push_back(dataItems->GetElement(i)->GetStatismoDataItem());
		}


		statismo::StatisticalModel<T>* model_statismo = callstatismoImpl(std::tr1::bind(&ImplType::BuildNewModel, this->m_impl, dataItemsStatismo, noiseVariance, computeScores));
		typename StatisticalModel<T>::Pointer model_itk = StatisticalModel<T>::New();
		model_itk->SetstatismoImplObj(model_statismo);
		return model_itk;
	}


private:
	PCAModelBuilder(const PCAModelBuilder& orig);
	PCAModelBuilder& operator=(const PCAModelBuilder& rhs);

	ImplType* m_impl;
};


}

#endif /* ITKMODELBUILDER_H_ */
