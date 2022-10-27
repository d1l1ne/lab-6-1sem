#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int try_catch_pos(string value);
int try_catch(string value);
bool check_array(string array[], int& elems_number);

void array_shift(int array[], int& count, int& array_length);
void array_output(int array[], int& elems_number);
void array_output_s(string array[], int& elems_number);

void dynamic_array();
void static_array();
void array_from_file();

int main() {

	string menu;
	int menu_int;

	while (true) {

		cout << endl << "1. Static array" << endl << "2. Dynamic array" << endl << "3. Array from file" << endl << "4. Close" << endl;
		cin >> menu;

		menu_int = try_catch(menu);

		if (menu_int == 1) {
			static_array();
		}
		else if (menu_int == 2) {
			dynamic_array();
		}
		else if (menu_int == 3) {
			array_from_file();
		}
		else if (menu_int == 4) {
			cout << "See you next time!" << endl;
			break;
		}
		else {
			cout << "Please enter correct value" << endl;
		}

	}


	system("pause");
	return 0;

}

void array_output(int array[], int& elems_number) {

	for (int k = 0; k < elems_number; k++) {

		cout << array[k] << " ";

	}

	cout << endl;

}

void array_output_s(string array[], int& elems_number) {

	for (int k = 0; k < elems_number; k++) {

		cout << array[k] << " ";

	}

	cout << endl;

}

void array_shift(int array[], int& count, int& array_length) {

	int temp, saved_value;

	for (int i = 0; i < count; i++) {

		for (int j = 0; j < array_length; j++) {


			if (j == 0) {

				saved_value = array[j];

			}
			else if (j == array_length - 1) {

				array[0] = array[j];
				array[j] = saved_value;

			}
			else {

				temp = array[j];
				array[j] = saved_value;
				saved_value = temp;

			}

		}

	}

	array_output(array, array_length);

}

void dynamic_array() {

	string length;
	cout << "Enter array's length: " << endl;
	cin >> length;

	int n = try_catch_pos(length);

	if (n > 0) {

		int* dynarray = new int[n];

		for (int q = 0; q < n; q++) {

			dynarray[q] = rand();

		}

		string scount_s;
		cout << "Enter shift count: " << endl;
		cin >> scount_s;

		cout << "Array:" << endl;
		array_output(dynarray, n);

		int scount = try_catch_pos(scount_s);
		
		if (scount > 0) {

			cout << "Array after shifting:" << endl;
			array_shift(dynarray, scount, n);

		}

	}

}

void static_array() {

	int first_array[5] = { 1, 2, 3, 4, 5 };
	string scount_s;
	int array_length = sizeof(first_array) / sizeof(*first_array);

	cout << "Enter shift count: " << endl;
	cin >> scount_s;

	cout << "Array:" << endl;
	array_output(first_array, array_length);

	int scount = try_catch_pos(scount_s);

	if (scount > 0) {

		cout << "Array after shifting" << endl;
		array_shift(first_array, scount, array_length);

	}

}

int try_catch_pos(string value) {

	int res = 0;

	try {

		res = stoi(value);

	}
	catch (invalid_argument) {

		cout << "Value must be integer" << endl;

	}
	catch (out_of_range) {

		cout << "Value is too big" << endl;

	}
	catch (exception) {

		cout << "Unknown exception" << endl;

	}

	if (res <= 0) {
		cout << "Value must be positive" << endl;
		res = 0;
	}

	return res;

}

int try_catch(string value) {

	int res = 0;

	try {

		res = stoi(value);

	}
	catch (invalid_argument) {

		cout << "Value must be integer" << endl;

	}
	catch (out_of_range) {

		cout << "Value is too big" << endl;

	}
	catch (exception) {

		cout << "Unknown exception" << endl;

	}

	return res;

}

bool check_array(string array[], int& elems_number) {

	bool state = true;
	for (int i = 0; i < elems_number; i++) {

		try {

			stoi(array[i]);

		}
		catch (exception) {

			state = false;
			break;

		}

	}
	return state;
}

void array_from_file() {

	ifstream file("C:/vremennoe/arrays.txt");

	if (file.is_open()) {

		int row_count = 0;
		string row;

		while (getline(file, row)) {

			if (row.empty() == false) {
				row_count++;
			}

		}

		file.close();

		if (row_count != 0) {

			ifstream file1("C:/vremennoe/arrays.txt");

			string* temparray = new string[row_count];
			row_count = 0;

			while (getline(file1, row)) {

				if (row.empty() == false) {
					temparray[row_count] = row;
					row_count++;
				}

			}

			file1.close();

			int saved, round(0);

			if (check_array(temparray, row_count)) {

				for (int t = 0; t < row_count; t++) {

					saved = try_catch_pos(temparray[t]);

					if (saved <= 0) {

						break;

					}
					if (round + saved < row_count) {

						int* small_array = new int[saved];

						for (int k = 0; k < saved; k++) {

							small_array[k] = try_catch(temparray[k + 1 + round]);

						}
						string scount_s;
						cout << "Enter shift count: " << endl;
						cin >> scount_s;

						int scount = try_catch_pos(scount_s);

						round += saved + 1;
						cout << "Array:" << endl;
						array_output(small_array, saved);
						cout << "Array after shifting:" << endl;
						array_shift(small_array, scount, saved);
						cout << endl;

						t += saved;

						if (t >= row_count - 1) {

							break;

						}

					}
					else {

						cout << "Not enough values in next array" << endl;
						break;

					}

				}


			}
			else {

				cout << "File has invalid values" << endl;

			}

		}
		else {

			cout << "File is empty" << endl;

		}

	}
	else {

		cout << "Can't reach the file" << endl;

	}

}