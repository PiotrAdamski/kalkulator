#include <gtk/gtk.h>
#include <iostream>
#include <string>
#include "math.h"
#include <fstream>

using namespace std;

//globalna deklaracja elementow okna jako globalne
GtkWidget * okno;
GtkWidget * wejscie;
GtkWidget * etykieta;
GtkWidget * kontajner;
int wynik = 0;

//funkcja wykonujaca tresc zadania
void przeliczaj()
{
    //algorytm
    int  stos[256], ws = 0;
    int  a, b, w;
    char el[256];
    int iter = 0;

    string wyrazenie = gtk_entry_get_text(GTK_ENTRY(wejscie));
    int lastCharIndex = wyrazenie.size()-1;
    if (wyrazenie[lastCharIndex] == '='){
        do
        {
            el[0] = wyrazenie[iter];

            iter++;
            if(el[0] >= '0' && el[0] <= '9')
            {
                a = b = 0;
                do a = 10 * a + el[b++] - 48; while(el[b]);
                stos[ws++] = a;
            }
            else if(el[0] == '=') wynik = stos[--ws];
            else
            {
                b = stos[--ws]; a = stos[--ws];

                switch(el[0])
                {
                    case '+': w = a + b; break;
                    case '-': w = a - b; break;
                    case '*': w = a * b; break;
                    case '/': w = a / b; break;
                    case '%': w = a % b; break;
                    case 'p': w =  pow( a,( 1 / b ) );break;//pierwiastek kazdego stopnia
                    case '^': w = 1;
                              while(b--) w *= a;
                              break;
                }

                stos[ws++] = w;
            }
        } while(el[0] != '=');

        gchar *str;
        str = g_strdup_printf ("%d", wynik);
        gtk_label_set_text( GTK_LABEL( etykieta ),str);
        ofstream plik;
        plik.open( "logi.log", ios::ate);
        if( plik.good() == true )
        {
            plik  << wyrazenie << wynik << endl;
            plik.close();
        }

    }else
    gtk_label_set_text( GTK_LABEL( etykieta ),"wprowadz poprawne wyrazenie.");
    wynik = 0;
}

int main( int argc, char * argv[] )
{
    gtk_init( & argc, & argv );

    okno = gtk_window_new( GTK_WINDOW_TOPLEVEL );
    gtk_window_set_title( GTK_WINDOW( okno ), "Kalkulator ONP" );
    gtk_window_set_position( GTK_WINDOW( okno ), GTK_WIN_POS_CENTER );
    gtk_window_set_default_size( GTK_WINDOW( okno ), 230, 60 );

    kontajner = gtk_vbox_new( FALSE, 1 );
    gtk_container_add( GTK_CONTAINER( okno ), kontajner );

    etykieta = gtk_label_new( "Tu wyswietli sie wynik." );
    gtk_container_add( GTK_CONTAINER( kontajner ), etykieta );

    wejscie = gtk_entry_new();
    gtk_container_add( GTK_CONTAINER( kontajner ), wejscie );

    g_signal_connect( G_OBJECT( wejscie ), "changed", G_CALLBACK( przeliczaj ), NULL );
    g_signal_connect( G_OBJECT( okno ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

    gtk_widget_show_all( okno );

    gtk_main();

    return 0;
}
