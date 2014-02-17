#include <gtk/gtk.h>
#include <iostream>
#include <string>

using namespace std;



//globalna deklaracja elementow okna
GtkWidget * okno;
GtkWidget * entry;
GtkWidget * etykieta;
GtkWidget * vbox;
int x = 0;
//funkcja wykonujaca tresc zadania
void przeliczaj()
{
    x++;
    string wynik = "wynik";
    gtk_label_set_text( GTK_LABEL( etykieta ), "hej" );
}

int main( int argc, char * argv[] )
{


    gtk_init( & argc, & argv );

    okno = gtk_window_new( GTK_WINDOW_TOPLEVEL );
    gtk_window_set_title( GTK_WINDOW( okno ), "Kalkulator ONP" );
    gtk_window_set_position( GTK_WINDOW( okno ), GTK_WIN_POS_CENTER );
    gtk_window_set_default_size( GTK_WINDOW( okno ), 230, 60 );

    vbox = gtk_vbox_new( FALSE, 1 );
    gtk_container_add( GTK_CONTAINER( okno ), vbox );

    etykieta = gtk_label_new( "Tu wyswietli sie wynik." );
    gtk_container_add( GTK_CONTAINER( vbox ), etykieta );

    entry = gtk_entry_new();
    gtk_container_add( GTK_CONTAINER( vbox ), entry );

    g_signal_connect( G_OBJECT( entry ), "changed", G_CALLBACK( przeliczaj ), NULL );
    g_signal_connect( G_OBJECT( okno ), "destroy", G_CALLBACK( gtk_main_quit ), NULL );

    gtk_widget_show_all( okno );

    gtk_main();

    return 0;
}
