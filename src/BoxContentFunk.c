#include "BoxContentFunk.h"

void content_login_container_box(GtkWidget *container)
{
    GtkWidget *textlabel, *submitbutton, *passentry, *labelnewuser;

    textlabel = gtk_label_new("Пароль");
    labelnewuser = gtk_label_new("Новий користувач");

    passentry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(passentry), FALSE);
    
    submitbutton = gtk_button_new_with_label("Вхід");
    g_signal_connect(submitbutton, "clicked", G_CALLBACK(login_button_clicked), passentry);

    gtk_box_append(GTK_BOX(container), textlabel);
    gtk_box_append(GTK_BOX(container), passentry);
    gtk_box_append(GTK_BOX(container), submitbutton);
    gtk_box_append(GTK_BOX(container), labelnewuser);
}

void content_header_box(GtkWidget *header)
{
    GtkWidget *entry_button, *card_button, *user_data_button;
    GtkWidget *entry_box, *card_box, *user_data_box;
    GtkWidget *entry_label, *card_label, *user_data_label;
    GtkWidget *entry_counter, *card_counter, *user_data_counter;
    GtkWidget *entry_image, *card_image, *user_data_image;

    entry_button = gtk_button_new();
    card_button = gtk_button_new();
    user_data_button = gtk_button_new();

    gtk_widget_set_size_request(entry_button, -1, 50);
    gtk_widget_set_size_request(card_button, -1, 50);
    gtk_widget_set_size_request(user_data_button, -1, 50);

    entry_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    card_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
    user_data_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);

    entry_label = gtk_label_new("Вхід");
    card_label = gtk_label_new("Банк");
    user_data_label = gtk_label_new("Особисті дані");
    //fill all and position label in the button 
    gtk_widget_set_hexpand(entry_label, TRUE);
    gtk_widget_set_hexpand(card_label, TRUE);
    gtk_widget_set_hexpand(user_data_label, TRUE);
    gtk_widget_set_halign(entry_label, GTK_ALIGN_START);
    gtk_widget_set_halign(card_label, GTK_ALIGN_START);
    gtk_widget_set_halign(user_data_label, GTK_ALIGN_START);

    entry_counter = gtk_label_new("8");
    card_counter = gtk_label_new("5");
    user_data_counter = gtk_label_new("3");

    entry_image = gtk_image_new_from_file("img/global.png");
    card_image = gtk_image_new_from_file("img/credit-card.png");
    user_data_image = gtk_image_new_from_file("img/card.png");

    gtk_box_append(GTK_BOX(entry_box), entry_image);
    gtk_box_append(GTK_BOX(entry_box), entry_label);
    gtk_box_append(GTK_BOX(entry_box), entry_counter);
    
    gtk_box_append(GTK_BOX(card_box), card_image);
    gtk_box_append(GTK_BOX(card_box), card_label);
    gtk_box_append(GTK_BOX(card_box), card_counter);

    gtk_box_append(GTK_BOX(user_data_box), user_data_image);
    gtk_box_append(GTK_BOX(user_data_box), user_data_label);
    gtk_box_append(GTK_BOX(user_data_box), user_data_counter);

    gtk_button_set_child(GTK_BUTTON(entry_button), entry_box);
    gtk_button_set_child(GTK_BUTTON(card_button), card_box);
    gtk_button_set_child(GTK_BUTTON(user_data_button), user_data_box);

    gtk_box_append(GTK_BOX(header), entry_button);
    gtk_box_append(GTK_BOX(header), card_button);
    gtk_box_append(GTK_BOX(header), user_data_button);


}

void content_center_box(GtkWidget *content)
{
    GtkWidget *content_button[15], *content_box[15], *content_label[15];

    for(int i = 0; i < 15; i++)
    {
        content_button[i] = gtk_button_new();
        gtk_widget_set_size_request(content_button[i], -1, 50);

        content_box[i] = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 15);
        content_label[i] = gtk_label_new("Назва ресурсу пароля");
        gtk_widget_set_hexpand(content_label[i], TRUE);
        gtk_widget_set_halign(content_label[i], GTK_ALIGN_START);
        if(i < 8)
        {
            GtkWidget *entry_images = gtk_image_new_from_file("img/global.png");
            gtk_box_append(GTK_BOX(content_box[i]), entry_images);
        }
        else if(i < 12)
        {
            GtkWidget *card_images = gtk_image_new_from_file("img/credit-card.png");
            gtk_box_append(GTK_BOX(content_box[i]), card_images);
        }
        else
        {
            GtkWidget *user_data_images = gtk_image_new_from_file("img/card.png");
            gtk_box_append(GTK_BOX(content_box[i]), user_data_images);
        }
        gtk_box_append(GTK_BOX(content_box[i]), content_label[i]);
        gtk_button_set_child(GTK_BUTTON(content_button[i]), content_box[i]);
        gtk_box_append(GTK_BOX(content), content_button[i]);
    }
}

void content_footer_box(GtkWidget *footer)
{
    GtkWidget *add_button, *add_box, *add_label, *add_image;
    add_button = gtk_button_new();
    g_signal_connect(add_button, "clicked", G_CALLBACK(add_button_clicked), NULL);
    gtk_widget_set_size_request(add_button, -1, 50);

    add_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    add_label = gtk_label_new("Створити запис");
    add_image = gtk_image_new_from_file("img/plus.png");
    
    gtk_box_append(GTK_BOX(add_box), add_image);
    gtk_box_append(GTK_BOX(add_box), add_label);
    gtk_button_set_child(GTK_BUTTON(add_button), add_box);
    gtk_box_append(GTK_BOX(footer), add_button);
}

void content_add_pass_header_box(GtkWidget *header_box)
{
    GtkWidget *pass_box, *type_box, *name_box;
    GtkWidget *pass_label, *type_label, *name_label;
    GtkWidget *pass_entry, *type_entry, *name_entry;
    GtkWidget *generate_button;

    // Створюємо блоки для пароля, типу та імені
    pass_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    type_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // Створюємо мітки для полів пароля, типу та імені
    type_label = gtk_label_new("Тип");
    name_label = gtk_label_new("Ім'я");
    pass_label = gtk_label_new("Пароль");

    // Створюємо поля вводу для пароля, типу та імені
    type_entry = gtk_entry_new();
    name_entry = gtk_entry_new();
    pass_entry = gtk_entry_new();
    ptr_entry = pass_entry;

    // Створюємо кнопку "Генерувати"
    generate_button = gtk_button_new_with_label("Генерувати");
    g_signal_connect(generate_button, "clicked", G_CALLBACK(generate_button_clicked), pass_entry);

    // Додаємо мітки та поля вводу в блоки
    gtk_box_append(GTK_BOX(type_box), type_label);
    gtk_box_append(GTK_BOX(type_box), type_entry);

    gtk_box_append(GTK_BOX(name_box), name_label);
    gtk_box_append(GTK_BOX(name_box), name_entry);

    gtk_box_append(GTK_BOX(pass_box), pass_label);
    gtk_box_append(GTK_BOX(pass_box), pass_entry);

    // Додаємо блоки до заголовкового блоку
    gtk_box_append(GTK_BOX(header_box), type_box);
    gtk_box_append(GTK_BOX(header_box), name_box);
    gtk_box_append(GTK_BOX(header_box), pass_box);
    gtk_box_append(GTK_BOX(header_box), generate_button);
}

// Функція для додавання блоку властивостей пароля
void content_add_pass_properties_pass_box(GtkWidget *propertiespass_box)
{
    GtkWidget *scale_length_box, *min_number_box, *min_special_box;
    GtkWidget *length_scale_label, *max_length_scale_label, *name_min_label, *name_special_label, *counter_min_number_label, *counter_special_label;
    GtkWidget *scale_length_pass;
    GtkWidget *uppercase_checkbutton, *lowercase_checkbutton, *number_checkbutton, *specialchar_checkbutton;
    GtkWidget *plus_min_number_button, *minus_min_number_button, *plus_special_button, *minus_special_button;

    // Створюємо блок для шкали довжини пароля
    scale_length_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 7);
    min_number_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 7);
    min_special_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 7);
    gtk_widget_set_sensitive(min_number_box, FALSE);
    gtk_widget_set_sensitive(min_special_box, FALSE);

    // Створюємо мітки для мінімальної та максимальної довжини пароля
    length_scale_label = gtk_label_new("4");
    max_length_scale_label = gtk_label_new("30");

    name_min_label = gtk_label_new("Мінімальна кількість цифр:");
    name_special_label = gtk_label_new("Мінімальна кількість спец символів:");
    counter_min_number_label = gtk_label_new("1");
    gtk_widget_set_hexpand(counter_min_number_label, TRUE);
    gtk_label_set_xalign(GTK_LABEL(counter_min_number_label), 1.0);
    counter_special_label = gtk_label_new("1");
    gtk_widget_set_hexpand(counter_special_label, TRUE);
    gtk_label_set_xalign(GTK_LABEL(counter_special_label), 1.0);

    // Створюємо шкалу для вибору довжини пароля
    scale_length_pass = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 4, 30, 1);
    gtk_widget_set_hexpand(scale_length_pass, TRUE);
    g_signal_connect(scale_length_pass, "value-changed", G_CALLBACK(on_scale_value_changed), length_scale_label);

    // Створюємо прапорці для вибору властивостей пароля
    uppercase_checkbutton = gtk_check_button_new_with_label("Верхній регістр");
    g_signal_connect(uppercase_checkbutton, "toggled", G_CALLBACK(on_upper_checkbutton_press_event), NULL);
    lowercase_checkbutton = gtk_check_button_new_with_label("Нижній регістр");
    g_signal_connect(lowercase_checkbutton, "toggled", G_CALLBACK(on_lower_checkbutton_press_event), NULL);
    number_checkbutton = gtk_check_button_new_with_label("Числа");
    g_signal_connect(number_checkbutton, "toggled", G_CALLBACK(on_number_checkbutton_press_event), min_number_box);
    specialchar_checkbutton = gtk_check_button_new_with_label("Спеціальні символи");
    g_signal_connect(specialchar_checkbutton, "toggled", G_CALLBACK(on_special_checkbutton_press_event), min_special_box);

    plus_min_number_button = gtk_button_new_with_label("+");
    minus_min_number_button = gtk_button_new_with_label("-");
    plus_special_button = gtk_button_new_with_label("+");
    minus_special_button = gtk_button_new_with_label("-");

    g_signal_connect(plus_min_number_button, "clicked", G_CALLBACK(on_plus_min_number_button_clicked), counter_min_number_label);
    g_signal_connect(minus_min_number_button, "clicked", G_CALLBACK(on_minus_min_number_button_clicked), counter_min_number_label);
    g_signal_connect(plus_special_button, "clicked", G_CALLBACK(on_plus_special_button_clicked), counter_special_label);
    g_signal_connect(minus_special_button, "clicked", G_CALLBACK(on_minus_special_button_clicked), counter_special_label);

    // Додаємо мітки, шкалу та прапорці до блоку властивостей пароля
    gtk_box_append(GTK_BOX(scale_length_box), length_scale_label);
    gtk_box_append(GTK_BOX(scale_length_box), scale_length_pass);
    gtk_box_append(GTK_BOX(scale_length_box), max_length_scale_label);

    gtk_box_append(GTK_BOX(min_number_box), name_min_label);
    gtk_box_append(GTK_BOX(min_number_box), counter_min_number_label);
    gtk_box_append(GTK_BOX(min_number_box), minus_min_number_button);
    gtk_box_append(GTK_BOX(min_number_box), plus_min_number_button);
    gtk_box_append(GTK_BOX(min_special_box), name_special_label);
    gtk_box_append(GTK_BOX(min_special_box), counter_special_label);
    gtk_box_append(GTK_BOX(min_special_box), minus_special_button);
    gtk_box_append(GTK_BOX(min_special_box), plus_special_button);

    gtk_box_append(GTK_BOX(propertiespass_box), scale_length_box);
    gtk_box_append(GTK_BOX(propertiespass_box), uppercase_checkbutton);
    gtk_box_append(GTK_BOX(propertiespass_box), lowercase_checkbutton);
    gtk_box_append(GTK_BOX(propertiespass_box), number_checkbutton);
    gtk_box_append(GTK_BOX(propertiespass_box), specialchar_checkbutton);
    gtk_box_append(GTK_BOX(propertiespass_box), min_number_box);
    gtk_box_append(GTK_BOX(propertiespass_box), min_special_box);
}
