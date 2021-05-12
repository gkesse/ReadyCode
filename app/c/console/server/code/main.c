//===============================================
#include <gtk/gtk.h>
//===============================================
static void GWindow_OnDestroy(GtkWidget* obj, gpointer params);
//===============================================
int main(int argc, char** argv) {
    gtk_init(&argc, &argv);
    
    GtkWidget* lWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(lWindow), "ReadyApp");
    gtk_container_set_border_width(GTK_CONTAINER(lWindow), 0);
    gtk_widget_set_size_request(GTK_WIDGET(lWindow), 400, 200);
    
    GtkWidget* label = gtk_label_new ("Double-Click Me!");
    
    GtkWidget* eventbox = gtk_event_box_new ();
    gtk_container_add (GTK_CONTAINER (eventbox), label);
      
    gtk_container_add(GTK_CONTAINER(lWindow), eventbox);
    gtk_widget_show_all(lWindow);
    
    g_signal_connect(G_OBJECT(lWindow), "destroy", G_CALLBACK(GWindow_OnDestroy), NULL);
    
    gtk_main();
    return 0;
}
//===============================================
static void GWindow_OnDestroy(GtkWidget* obj, gpointer params) {
    gtk_main_quit();
}
//===============================================
