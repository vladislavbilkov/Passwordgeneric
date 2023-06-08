#include <gtk/gtk.h>

#include "WindowContentFunk.h"

//ініціалізація
static void activate(GtkApplication* app, gpointer user_data)
{
    content_login_window(app);
}

int main(int argc, char *argv[])
{
    GtkApplication *app;
    int status;

    app = gtk_application_new ("org.gtk.example", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
    status = g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);

    return status;
}
