
#include "Locale.h"
#include "Principale.h"
using namespace std;

int main()
{
    Locale s("Altavilla", 3);
    cout << s.get_distance() << " " << s.get_name();
    try{
        bool d = s.is_arriving(0, 1);
        cout <<endl << d << endl;
    }catch(exception)
    {
        cout<<"Imbecille";
    }

    Locale g("Lerino", 20);
    cout << g.get_distance() << " " << g.get_name();
    try {
        bool k = g.is_arriving(0, 2);
        cout << endl << k << endl;
    }
    catch (exception)
    {
        cout << "Imbecille";
    }

    cout << endl << endl << endl;

    Principale n ("Padova", 20);
    cout << n.get_distance() << " " << n.get_name();
    try {
        bool l = n.is_arriving(0);
        cout << endl << l << endl ;
    }
    catch (exception)
    {
        cout << "Imbecille";
    }

    try {
        int l = n.is_arriving(1);
        cout << endl << l;
    }
    catch (exception)
    {
        cout << "Imbecille";
    }

    try {
        int l = n.is_arriving(1);
        cout << endl << l;
    }
    catch (exception)
    {
        cout << "Imbecille";
    }
    
    try {
        int m = n.is_arriving(1);
        if (m == 0)
            cout << endl << "Non c'e' posto";
        else if (m == 1)
            cout << "C'e' posto";
    }
    catch (exception)
    {
        cout << "Imbecille";
    }
    cout << endl << endl << endl;
    return 0;
}
