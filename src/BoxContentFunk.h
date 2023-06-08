#pragma once

#include "ConectSignalFunk.h"

#include <gtk/gtk.h>

GtkWidget *ptr_entry;

void content_login_container_box(GtkWidget *container);
void content_header_box(GtkWidget *header);
void content_center_box(GtkWidget *content);
void content_footer_box(GtkWidget *footer);
void content_add_pass_header_box(GtkWidget *header_box);
void content_add_pass_properties_pass_box(GtkWidget *propertiespass_box);