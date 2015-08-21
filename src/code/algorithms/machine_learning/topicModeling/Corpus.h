///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Single object detection - ObjectDetector
//		Author: Pablo R.S.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef _BOVIL_ALGORITHMS_MACHINELEARNING_TOPICMODELING_CORPUS_H_
#define _BOVIL_ALGORITHMS_MACHINELEARNING_TOPICMODELING_CORPUS_H_

#include "Document.h"

#include <vector>

namespace algorithm {
	class Corpus {
	public:
		void addDocument(Document _document){ mDocuments.push_back(_document); };

		unsigned totalWords(){
			unsigned numWords = 0;
			for (Document doc : mDocuments) {
				numWords += doc.lenght();
			}
			return numWords;
		};
		unsigned numDocs(){return mDocuments.size();};

		Document document(unsigned _index){return mDocuments[_index]; };

	private:
		std::vector<Document> mDocuments;
	};	//	class Corpus

}	//	namespace algorithm

#endif	//	_BOVIL_ALGORITHMS_MACHINELEARNING_TOPICMODELING_CORPUS_H_