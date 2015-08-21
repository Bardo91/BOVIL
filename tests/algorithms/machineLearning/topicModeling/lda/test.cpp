///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		BOViL: Bardo Open Vision Libraries
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//

#include <algorithms/machine_learning/topicModeling/lda.h>
#include <algorithms/machine_learning/topicModeling/Document.h>
#include <algorithms/machine_learning/topicModeling/Corpus.h>

#include <string>
#include <vector>

using namespace BOViL::algorithms;
using namespace std;

const vector<string> cVocabulary = {"casa", "cocina", "salon", "baño", "cama", "patio", "nevera", "lavadora", "sofa", "television",
									"moto","coche","carrera","motor","gasolina","diesel","bujia","volante","aceite","transmision",
									"espaguetis","aceite","nevera","croquetas","sandia","platano","carne","pescado","filete","pan",
									"perro","gato","leon","gacela","lagarto","tigre","guepardo","serpiente","araña","lobo"};

Document generateDoc(unsigned _topic, unsigned _size);

int main(int _argc, char** _argv) {
	Corpus trainCorpus;
	for (unsigned i = 0; i < 20; i++) {
		trainCorpus.addDocument(generateDoc(20%4, 100));
	}
	
	LDA model;
	model.train(trainCorpus, 4, 4*10, 0.1, 2, 100);

}

Document generateDoc(unsigned _topic, unsigned _size){
	Document doc;

	for (unsigned i = 0; i < _size; i++) {
		if (double(rand()) / RAND_MAX > 0.8) {	// Add word of main topic.
			unsigned randWord = (unsigned) round((double(rand()) / RAND_MAX)*10);
			doc.addWord(10*_topic + randWord);
		}
		else {	// Add word from other topic.
			unsigned randTopic = (unsigned) round((double(rand()) / RAND_MAX)*3);
			unsigned randWord = (unsigned) round((double(rand()) / RAND_MAX)*10);
			doc.addWord(10*randTopic + randWord);
		}
	}

	return doc;
}
