//===============================================
#include <gtk/gtk.h>
//===============================================
#define NUM_NAMES 4
const gchar* names[] = { "Andrew", "Joe", "Samantha", "Jonathan" };
//===============================================
static void GWindow_OnDestroy(GtkWidget* obj, gpointer params);
//===============================================
int main(int argc, char** argv) {
    gtk_init(&argc, &argv);
    
    GtkWidget* lWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(lWindow), "ReadyApp");
    gtk_container_set_border_width(GTK_CONTAINER(lWindow), 0);
    gtk_widget_set_size_request(GTK_WIDGET(lWindow), 400, 200);
    
    GtkWidget* vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 5);

    for (int i = 0; i < NUM_NAMES; i++) {
        GtkWidget *button = gtk_button_new_with_label (names[i]);
        gtk_box_pack_start(GTK_BOX (vbox), button, 1, 0, 0);

        g_signal_connect_swapped (G_OBJECT (button), "clicked", G_CALLBACK (gtk_widget_destroy), (gpointer) button);
    }

    gtk_container_add(GTK_CONTAINER(lWindow), vbox);
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
