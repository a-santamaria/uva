#include <iostream>

using namespace std;

int main() {
    int casos;
    cin>>casos;
    int cont = 1;
    while(casos--) {
        int n;
        cin>>n;
        n--;
        int arr[n];

        for(int i = 0; i < n; i++)
            cin>>arr[i];

        int mayor = arr[0];
        int ind = 0;
        int solInd = 0;
        int solfin = 0;
        int sum = arr[0];
        //cout<<"intit sum "<<sum<<endl;
        for(int i = 1; i < n; i++) {
            if(arr[i] > arr[i] + sum) {
                //cout<<"reset --- ";
                sum = arr[i];
                ind = i;
            } else {
                //cout<<"add --- ";
                sum += arr[i];
            }
            //cout<<"sum "<<sum<<endl;
            if(sum > mayor) {
                mayor = sum;
                solInd = ind;
                solfin = i;
            } else if(sum == mayor) {
                if(i - ind > solfin - solInd) {
                    solfin = i;
                    solInd = ind;
                }
            }
        }
        //cout<<"mayor "<<mayor<<endl;
        if(mayor >= 0)
            cout<<"The nicest part of route " << cont++ << " is between stops " << solInd+1 << " and " << solfin+2 << endl;
        else
            cout<<"Route " << cont++ << " has no nice parts" <<endl;
    }
    return 0;
}
