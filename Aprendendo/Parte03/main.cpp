#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	fstream arquivo;
	char linha[60];
	
	arquivo.open("/dev/memory");
	
	arquivo.write("Ola Mundo a", 11);
	
	arquivo.read(linha, 11);
	
	cout << "linha: " << linha << endl;
	
	arquivo.close();
	
	cout << "\nOk!\n" << endl;
	
	return 0;
}
