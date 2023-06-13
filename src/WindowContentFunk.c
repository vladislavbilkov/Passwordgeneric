#include "WindowContentFunk.h"

void content_main_window(GtkApplication* app)
{
    GtkWidget *window, *container;
    GtkWidget *header, *scroll, *content, *footer;
    
    window = gtk_application_window_new(app);
    
    gtk_window_set_title(GTK_WINDOW(window), "Генератор паролів");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);
    container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    gtk_window_set_child(GTK_WINDOW(window), container);
    
    //create header box and apend to container
    header = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    content_header_box(header);
    gtk_box_append(GTK_BOX(container), header);
   
    //create and append content box make him scroller
    scroll = gtk_scrolled_window_new();
    content = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    
    //займає все доступне місце
    gtk_widget_set_hexpand(scroll, TRUE);
    gtk_widget_set_vexpand(scroll, TRUE);

    content_center_box(content);
    gtk_box_append(GTK_BOX(container), scroll);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scroll), content);
    
    //create and append container footer
    footer = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    content_footer_box(footer);
    gtk_box_append(GTK_BOX(container), footer);

    gtk_window_present(GTK_WINDOW(window));
}

void content_login_window(GtkApplication* app)
{
    GtkWidget *window, *container;

    //create main window and set child
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Вхід");
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 200);

    container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);

    content_login_container_box(container);

    gtk_window_set_child(GTK_WINDOW(window), container);


    // show window and run main cycle GTK
    gtk_window_present(GTK_WINDOW(window));

}