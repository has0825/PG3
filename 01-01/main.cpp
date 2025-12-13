#include <iostream>
#include <list>
#include <iterator>
#include <string>
using namespace std;

int main() {
	list<const char*> stations = {
		"Tokyo", "Kanda", "Akihabara", "Okachimachi", "Ueno",
		"Uguisudani", "Nippori", "Tabata", "Komagome", "Sugamo",
		"Otsuka", "Ikebukuro", "Mejiro", "Takadanobaba", "Shin-Okubo",
		"Shinjuku", "Yoyogi", "Harajuku", "Shibuya", "Ebisu",
		"Meguro", "Gotanda", "Osaki", "Shinagawa", "Tamachi",
		"Hamamatsucho", "Shimbashi", "Yurakucho"
	};

	cout << "Yamanote Line (1970):" << endl;
	for (auto s : stations) {
		cout << s << " ";
	}
	cout << endl << endl;

	{
		auto it = stations.begin();
		while (it != stations.end()) {
			if (string(*it) == "Tabata") {
				stations.insert(it, "Nishi-Nippori");
				break;
			}
			++it;
		}
	}

	cout << "Yamanote Line (2019):" << endl;
	for (auto s : stations) {
		cout << s << " ";
	}
	cout << endl << endl;

	{
		auto it = stations.begin();
		while (it != stations.end()) {
			if (string(*it) == "Tamachi") {
				stations.insert(it, "Takanawa Gateway");
				break;
			}
			++it;
		}
	}

	cout << "Yamanote Line (2022):" << endl;
	for (auto s : stations) {
		cout << s << " ";
	}
	cout << endl << endl;

	return 0;
}