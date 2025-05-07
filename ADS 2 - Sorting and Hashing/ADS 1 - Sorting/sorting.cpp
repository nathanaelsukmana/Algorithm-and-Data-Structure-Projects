// ADS Praktikum 2.1 Sortieren
// Name: Max Mustermann
#include "sorting.h"

namespace sorting {

	//****************
	// InsertionSort *
	//****************
	void InsertionSort(vector<int>& arr, int n)
	{	

		//einzufuegendes element suchen
		for(int i = 1; i < n; i++){ //beginnt von zweite element
			int tmp = arr[i];
			//linke element
			int j = i-1;

			//einfuegestelle suchen
			while(j >= 0 && arr[j] > tmp){ //linke element vergleich mit tmp
				arr[j+1] = arr[j];
				j--;
			}

		//einzufuegendes element an richtige stelle bringen
		arr[j+1] = tmp;
		}
	}


	//************
	// QuickSort *
	//************

	int Partition(vector<int>& arr, int p, int r){ //divide und letzte pos pivot bestimmen
		int x = arr[r]; //letzte element als pivot
		int i = p - 1;	//i beginnt vor anfangsindex

		//loop von links bis vor pivot
		for(int j = p; j <= r - 1; j++){
			if(arr[j] <= x){ //vergleich mit pivot
				i++;
				swap(arr[i], arr[j]);
			}

		}

		swap(arr[i+1], arr[r]);

		//arrayindex des pivot elementes
		return i+1;
	}

	//linker teil und rechter teil sortieren
	void QuickSort(vector<int>& arr, int left, int right)
	{
		if(left < right){
			int pivotIndex = Partition(arr, left, right); //arrayindex des pivot elementes
			QuickSort(arr, left, pivotIndex - 1); //linker teil
			QuickSort(arr, pivotIndex + 1, right); //rechter teil
		}
	}


	//************
	// MergeSort *
	//************
	//sortieren und kombieneren kleinerer stuecken array
	void Merge(vector<int>& a, vector<int>& b, int low, int pivot, int high)
	{
		//i = links, j = rechts, k = temp
		int i = low, j = pivot + 1, k = low;

		//mische die teilfolgen in temporaere array b
		while(i <= pivot && j <= high){
			if(a[i] <= a[j]){
				b[k] = a[i];
				i++;
			} else {
				b[k] = a[j];
				j++;
			}
			k++;
		}

		//falls rechte teilfolge fertig, uebernehme den rest der linken teilfolge
		while(i <= pivot){
			b[k++] = a[i++];
		}

		//falls linke teilfolge fertig, uebernehme rest von rechter teilfolge
		while(j <= high){
			b[k++] = a[j++];
		}

		//kopieren merged element zu original array
		for(int x = low; x <= high; x++){
			a[x] = b[x];
		}

	}

	//aufteilung array in kleinere stuecke
	void MergeSort(vector<int>& a, vector<int>& b, int low, int high)
	{
		if(low < high){
			int middle = (low + high)/2;

			MergeSort(a, b, low, middle); //linker teil

			MergeSort(a, b, middle + 1, high); //rechter teil

			Merge(a, b, low, middle, high);
		}
	}


	//************
	// Heapsort  *
	//************
	
	//kindknoten mit max heap sicherstellen
	void heapify(vector<int> &a, int n, int i) //n = anzahl element, den heapify werden
	{
		int kindlinks = (i * 2) + 1, kindrecht = (i * 2) + 2; //pos kindlinks und kindrechts berechnen, denn heap als array dargestellt

		int groesste = i;
		
		//max heap: kindlinks > root oder i
		if(kindlinks < n && a[kindlinks] > a[groesste]){
			groesste = kindlinks;
		}

		//kindrecht > i oder derzeitige groesste element
		if(kindrecht < n && a[kindrecht] > a[groesste]){
			groesste = kindrecht;
		}

		//kind grosser als root
		if(groesste != i){
			swap(a[i], a[groesste]);
			heapify(a, n, groesste);
		}
	}

	//sortieren
	void HeapSort(vector<int> &a, int n) //n = a.size()
	{	
		//max heap
		for(int i = (n/2)-1; i >= 0; i--){ //(n/2) - 1 : endeindux im array
			heapify(a, n, i);
		}

		//sortieren
		for(int i = n-1; i > 0; i--){
			swap(a[0], a[i]); //groesste element wechseln mit letzte element
			heapify(a, i, 0); //max heap fuer rest array
		}
	}

	//************
	// Shellsort *
	//************
	// Hier soll Hibbard implementiert werden
	void ShellSort_2n(vector<int> &a, int n)
	{

		//hibbard = {1, 3, 7, ..}
		vector<int>hibbard;
		//hibbard = [1]
		hibbard.push_back(1);
		//hinzuefuegen mehr element ins hibbard
		while(hibbard.back() < n){
			hibbard.push_back(2*hibbard.back() + 1);
		}

		//letzte gap loeschen wenn gap groesser oder gleich wie n
		if(hibbard.back() >= n){
			hibbard.pop_back();
		}

		//von groesste gap bis kleinste gap
		for(int i = hibbard.size() - 1; i >= 0; i--){
			int gap = hibbard[i];
			
			//iteration jeder gap
			for(int j = gap; j < n; j++){
				for(int k = j; k >= gap && a[k-gap] > a[k]; k -= gap){ //k-= gap bedeutet zuruck wie gap anzahl, 3 3 3
					swap(a[k], a[k-gap]);
				}
			}
		}
	}

	// Hier soll 2^i implementiert werden
	void ShellSort_2Square(vector<int>& a, int n)
	{
		vector<int> gaps;

		//gap list mit 2^i
		for(int i = 1; i <= n; i *= 2){
			gaps.push_back(i);
		}

		//von groesstem gap bis kleinste
		for(int i = gaps.size() - 1; i>=0; i--){
			int gap = gaps[i];

			//insertion sort mit gap
			for(int j = gap; j < n; j++){
				for(int k = j; k >= gap && a[k-gap] > a[k]; k -= gap){
					swap(a[k], a[k-gap]);
				}
			}
		}
	}

	//***************
	// CountingSort *
	//***************
	void CountingSort(vector<int>& a, int left, int right)
	{
		//nur ein element/kein element
		if(left >= right){
			return;
		}

		//groesste zahl in array suchen
		int groesste = a[left];
		for(int i = left + 1; i <= right; i++){
			if(a[i] > groesste){
				groesste = a[i];
			}
		}

		//neue array erstellen mit groesstem zahl als hoechste index 
		vector<int> neu_a(groesste + 1, 0);

		//frequenz: wie oft eine zahl im array vorkommt berechnen
		for(int i = left; i <= right; i++){
			neu_a[a[i]]++;	//speichert die haeufigkeit im neu_a
		}

		//erzeugt die sortierte zahlenfolge aus neu_a
		int final = left;
		for(int i = 0; i <= groesste; i++){
			while(neu_a[i] > 0){
				a[final] = i;
				final++;
				neu_a[i]--;
			}
		}
	}

	//************
	// RadixSort *
	//************
	//array A sortieren ausgehend von ziffer an der k ten
	void SortByDigit(vector<int>& A, int left, int right, int k){
		
		//digit 0-9
		const int R = 10;
		vector<int> Count(R, 0);
		vector<int> Pos(R,0);
		vector<int> B(right - left + 1);

		//count array initialisieren
		for (int j = 0; j < R; j++) {
        	Count[j] = 0; //haeufigkeit jede ziffer vorkommen
    	}

		//zaehle wie oft diese ziffer an der k-ten stelle vorkommt
		for (int i = left; i <= right; i++) {
        	int digit = (A[i] / k) % 10; //digit finden
        	Count[digit]++; //speichert die haeufigkeit im array count
    	}

		//pos array berechnen
		Pos[0] = left;
    	for (int j = 1; j < R; j++) {
        	Pos[j] = Pos[j - 1] + Count[j - 1];
    	}

		//array B mit k ten ziffer fuellen
		for (int i = left; i <= right; i++) {
        	int digit = (A[i] / k) % 10;
        	B[Pos[digit] - left] = A[i]; // offset dengan -left karena B dimulai dari indeks 0
        	Pos[digit]++;
    	}

		//B ins A kopieren, denn b ist ein der k ten ziffer aufsteigend sortiert
		for(int i = left; i <= right; i++){
			A[i] = B[i-left];
		}
	}

	void RadixSort(vector<int>& arr, int left, int right)
	{

		//groesste wert suchen
		int max = arr[left];
		for(int i = left + 1; i<= right; i++){
			if(arr[i] > max){
				max = arr[i];
			}
		}

		//maximale anzahl dezimalstellen 
		/*int k_max = 0;
		while(max > 0){
			k_max++;
			max /= 10;
		}*/

		//sortbydigit fuer jede digit
		for(int k = 1; max / k > 0; k *= 10){
			SortByDigit(arr, left, right, k);
		}
	}

	

  void randomizeVector(vector<int> &array, int n) {
    array.resize(n);

    for(unsigned int i=0;i<array.size();i++)
      array[i]=rand() % 1000000;
  }


}





