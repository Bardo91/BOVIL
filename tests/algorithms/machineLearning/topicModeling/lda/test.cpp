///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <algorithms/machine_learning/topicModeling/lda.h>
#include <algorithms/machine_learning/topicModeling/Document.h>
#include <algorithms/machine_learning/topicModeling/Corpus.h>

#include <cassert>
#include <string>
#include <vector>

using namespace BOViL::algorithms;
using namespace std;

const vector<string> cVocabulary = {"casa", "cocina", "salon", "baño", "cama", "patio", "nevera", "lavadora", "sofa", "television",
									"moto","coche","carrera","motor","gasolina","diesel","bujia","volante","aceite","transmision",
									"espaguetis","aceite","nevera","croquetas","sandia","platano","carne","pescado","filete","pan",
									"perro","gato","leon","gacela","lagarto","tigre","guepardo","serpiente","araña","lobo"};


Document generateDoc(unsigned _topic, unsigned _size);
void trainModel();
void newInference();

//---------------------------------------------------------------------------------------------------------------------
int main(int _argc, char** _argv) {
	
	trainModel();
	newInference();
	
}

//---------------------------------------------------------------------------------------------------------------------
Document generateDoc(unsigned _topic, unsigned _size){
	Document doc;

	for (unsigned i = 0; i < _size; i++) {
		if (double(rand()) / RAND_MAX < 0.8) {	// Add word of main topic.
			unsigned randWord = (unsigned) round((double(rand()) / RAND_MAX)*9);
			doc.addWord(10*_topic + randWord);
		}
		else {	// Add word from other topic.
			unsigned randTopic = (unsigned) round((double(rand()) / RAND_MAX)*3);
			unsigned randWord = (unsigned) round((double(rand()) / RAND_MAX)*9);
			doc.addWord(10*randTopic + randWord);
		}
	}

	return doc;
}

//---------------------------------------------------------------------------------------------------------------------
void trainModel(){
	// Generate random documents using vocabulary. Vocabulary has 40 words of 4 topics (10 words per topic).
	// Topics are: 0, 1, 2, 3, 0, 1, 2, 3, 0... etc.
	Corpus trainCorpus;
	for (unsigned i = 0; i < 100; i++) {
		trainCorpus.addDocument(generateDoc(i%4, 100));
	}

	// Train model
	LDA model;
	model.train(trainCorpus, 4, 4*10, 0.1, 2, 200);
	// Store Model
	model.save("ldaModel");
}

//---------------------------------------------------------------------------------------------------------------------
void newInference() {
	LDA model;	
	model.load("ldaModel"); // Load model

	// Generate random corpus for testing.
	Corpus evaluateCorpus;
	for (unsigned i = 0; i < 20; i++) {
		evaluateCorpus.addDocument(generateDoc(i%4, 100));
	}

	vector<vector<double>> topicProbs = model.evaluate(evaluateCorpus, 100);

	// Check inference of documents's topic.
	for (unsigned i = 0; i < topicProbs.size(); i++) {
		unsigned maxIndex = 0;
		double maxProb = 0.0;
		for (unsigned k = 0; k < topicProbs[i].size(); k++) {
			if (maxProb < topicProbs[i][k]) {
				maxIndex = k;
				maxProb = topicProbs[i][k];
			}
		}

		assert(maxProb > 0.8);
	}
}
