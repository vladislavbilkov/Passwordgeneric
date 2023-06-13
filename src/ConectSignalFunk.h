#pragma once

#include <gtk/gtk.h>
#include <openssl/aes.h>
#include <stdio.h>
#include "WindowContentFunk.h"

void login_button_clicked(GtkButton *button, GtkWidget *passentry);

void add_button_clicked(GtkButton *button, gpointer user_data);

gchar *generate_pass();
void on_scale_value_changed(GtkRange *range, GtkWidget *length_scale_label);
gboolean on_number_checkbutton_press_event(GtkWidget *widget, GtkWidget *box);
gboolean on_special_checkbutton_press_event(GtkWidget *widget, GtkWidget *box);
gboolean on_lower_checkbutton_press_event(GtkWidget *widget, gpointer user_data);
gboolean on_upper_checkbutton_press_event(GtkWidget *widget, gpointer user_data);
void on_plus_min_number_button_clicked(GtkButton *button, GtkWidget *label);
void on_minus_min_number_button_clicked(GtkButton *button, GtkWidget *label);
void on_plus_special_button_clicked(GtkButton *button, GtkWidget *label);
void on_minus_special_button_clicked(GtkButton *button, GtkWidget *label);
void login_button_clicked(GtkButton *button, GtkWidget *passentry);
void generate_button_clicked(GtkButton *button, gpointer user_data);
void add_button_clicked(GtkButton *button, gpointer user_data);
void content_main_window(GtkApplication *app);

void add_new_user_label_clicked(GtkLabel *label, gpointer user_data);

void check_password_length(GtkWidget *button, GtkWidget *passentry);

void aes_encrypt(const char *input, const char *key, char *output);

void aes_decrypt(const char *input, const char *key, char *output);

void on_add_pass_button_clicked(GtkButton *button, gpointer user_data);

void button_item_clicked(GtkButton *button, gpointer user_data);
