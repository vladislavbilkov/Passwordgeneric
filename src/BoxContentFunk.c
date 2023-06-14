#include "BoxContentFunk.h"

GtkWidget *entries[3];
GtkWidget *container_box;
GtkWidget *counters[3];

void content_login_container_box(GtkWidget *container)
{
    GtkWidget *textlabel, *submitbutton, *passentry, *newuserbutton;

    textlabel = gtk_label_new("Пароль");

    passentry = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(passentry), FALSE);
    
    submitbutton = gtk_button_new_with_label("Вхід");
    g_signal_connect(submitbutton, "clicked", G_CALLBACK(login_button_clicked), passentry);

    newuserbutton = gtk_button_new_with_label("Новий користувач");
    g_signal_connect(newuserbutton, "clicked", G_CALLBACK(add_new_user_label_clicked), NULL);

    gtk_box_append(GTK_BOX(container), textlabel);
    gtk_box_append(GTK_BOX(container), passentry);
    gtk_box_append(GTK_BOX(container), submitbutton);
    gtk_box_append(GTK_BOX(container), newuserbutton);
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
    user_data_label = gtk_label_new("Інші");
    //fill all and position label in the button 
    gtk_widget_set_hexpand(entry_label, TRUE);
    gtk_widget_set_hexpand(card_label, TRUE);
    gtk_widget_set_hexpand(user_data_label, TRUE);
    gtk_widget_set_halign(entry_label, GTK_ALIGN_START);
    gtk_widget_set_halign(card_label, GTK_ALIGN_START);
    gtk_widget_set_halign(user_data_label, GTK_ALIGN_START);

    entry_counter = gtk_label_new("0");
    card_counter = gtk_label_new("0");
    user_data_counter = gtk_label_new("0");

    counters[0] = entry_counter;
    counters[1] = card_counter;
    counters[2] = user_data_counter;

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
    FILE* file = fopen("bin/encrypted_passwords.bin", "rb");
    if (file != NULL) 
    {
        int num_passwords = 0;

        while (1) {
            size_t type_len, name_len, pass_len;

            if (fread(&type_len, sizeof(size_t), 1, file) != 1 ||
                fread(&name_len, sizeof(size_t), 1, file) != 1 ||
                fread(&pass_len, sizeof(size_t), 1, file) != 1) {
                break; // Помилка при зчитуванні довжини блоків
            }

            if (type_len == 0 || name_len == 0 || pass_len == 0) {
                break; // Недопустима довжина блоку
            }

            // Пропустити дані блоку
            fseek(file, type_len + name_len + pass_len, SEEK_CUR);

            num_passwords++;
        }

        // Використання отриманої кількості записів
        printf("Кількість записів: %d\n", num_passwords);

        // Повернутися до початку файлу
        rewind(file);

        //size_t max_text_length = AES_BLOCK_SIZE; // Максимальна довжина тексту
        char** encrypted_type = malloc(num_passwords * sizeof(char*));
        char** encrypted_name = malloc(num_passwords * sizeof(char*));
        char** encrypted_password = malloc(num_passwords * sizeof(char*));

        for (int i = 0; i < num_passwords; i++) {
            size_t type_len, name_len, pass_len;

            fread(&type_len, sizeof(size_t), 1, file);
            fread(&name_len, sizeof(size_t), 1, file);
            fread(&pass_len, sizeof(size_t), 1, file);

            encrypted_type[i] = malloc((type_len + 1) * sizeof(char));
            encrypted_name[i] = malloc((name_len + 1) * sizeof(char));
            encrypted_password[i] = malloc((pass_len + 1) * sizeof(char));

            fread(encrypted_type[i], sizeof(char), type_len, file);
            fread(encrypted_name[i], sizeof(char), name_len, file);
            fread(encrypted_password[i], sizeof(char), pass_len, file);

            encrypted_type[i][type_len] = '\0'; // Додати завершуючий символ '\0'
            encrypted_name[i][name_len] = '\0';
            encrypted_password[i][pass_len] = '\0';
        }
        fclose(file);

        int counter_type_login = 0;
        int counter_type_bank = 0;
        int counter_type_another = 0;

        // Додавання кнопок для кожного елементу
        for (int i = 0; i < num_passwords; i++) 
        {
            // Створення горизонтального контейнера для кожного елементу
            GtkWidget *item_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
            gtk_box_set_homogeneous(GTK_BOX(item_box), TRUE);
            gtk_box_append(GTK_BOX(content), item_box);

            // Створення кнопки з іменем
            GtkWidget *button = gtk_button_new();
            GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

            // Визначення типу та вибір відповідної картинки
            GtkWidget *image = NULL;

            
            if (strcmp(encrypted_type[i], "Вхід") == 0) {
                image = gtk_image_new_from_file("img/global.png");
                counter_type_login++;
            } else if (strcmp(encrypted_type[i], "Банк") == 0) {
                image = gtk_image_new_from_file("img/credit-card.png");
                counter_type_bank++;
            } else if(strcmp(encrypted_type[i], "Інші") == 0) {
                image = gtk_image_new_from_file("img/card.png");
                counter_type_another++;
            }

            gtk_box_append(GTK_BOX(box), image);

            // Створення етикетки з іменем
            GtkWidget *name_label = gtk_label_new(encrypted_name[i]);
            gtk_box_append(GTK_BOX(box), name_label);

            // Додавання вертикального контейнера до кнопки
            gtk_button_set_child(GTK_BUTTON(button), box);

            g_signal_connect(button, "clicked", G_CALLBACK(button_item_clicked), item_box);
            gtk_box_append(GTK_BOX(item_box), button);

            // Створення етикетки для паролю (початково прихована)

            char password_text[256];
            snprintf(password_text, sizeof(password_text), "Пароль: %s", encrypted_password[i]);

            GtkWidget *password_label = gtk_label_new(password_text);
            gtk_widget_set_visible(password_label, FALSE);
            gtk_widget_set_hexpand(password_label, TRUE);
            gtk_label_set_xalign(GTK_LABEL(password_label), 0.0);
            gtk_widget_set_margin_start(password_label, 10);
            gtk_box_append(GTK_BOX(item_box), password_label);

            // Створення кнопки видалення
            GtkWidget *delete_button = gtk_button_new();
            GtkWidget *delete_image = gtk_image_new_from_file("img/trash.png");
            gtk_widget_set_hexpand(delete_button, FALSE);
            gtk_widget_set_halign(delete_button, GTK_ALIGN_END);
            gtk_button_set_child(GTK_BUTTON(delete_button), delete_image);

            // Визначення видимості кнопки видалення
            gtk_widget_set_visible(delete_button, FALSE);

            // Додавання кнопки видалення до контейнера
            gtk_box_append(GTK_BOX(item_box), delete_button);

            // З'єднання обробника події для кнопки видалення
            //g_signal_connect(delete_button, "clicked", G_CALLBACK(delete_button_clicked), item_box);
        }

        char text[20];
        sprintf(text, "%d", counter_type_login);
        gtk_label_set_text(GTK_LABEL(counters[0]), text);

        sprintf(text, "%d", counter_type_bank);
        gtk_label_set_text(GTK_LABEL(counters[1]), text);

        sprintf(text, "%d", counter_type_another);
        gtk_label_set_text(GTK_LABEL(counters[2]), text);

        for (int i = 0; i < num_passwords; i++) {
            free(encrypted_type[i]);
            free(encrypted_name[i]);
            free(encrypted_password[i]);
        }
        free(encrypted_type);
        free(encrypted_name);
        free(encrypted_password);

    }
    else 
    {
        printf("Помилка відкриття файлу.\n");
    }
    container_box = content;

    /*char decrypted_type[AES_BLOCK_SIZE];
    char decrypted_name[AES_BLOCK_SIZE];
    char decrypted_password[AES_BLOCK_SIZE];

    if (file != NULL) 
    {
        fread(encrypted_type, sizeof(char), AES_BLOCK_SIZE, file);
        fread(encrypted_name, sizeof(char), AES_BLOCK_SIZE, file);
        fread(encrypted_password, sizeof(char), AES_BLOCK_SIZE, file);
        fclose(file);

        g_print("File text--------\n");
        g_print("Type: %s\n", encrypted_type);
        g_print("Name: %s\n", encrypted_name);
        g_print("Password: %s\n", encrypted_password);

        const char *key = "my_secret_key";

        aes_decrypt(encrypted_type, key, decrypted_type);
        aes_decrypt(encrypted_name, key, decrypted_name);
        aes_decrypt(encrypted_password, key, decrypted_password);

        g_print("Decriped text------------\n");
        g_print("Decrypted Type: %s\n", decrypted_type);
        g_print("Decrypted Name: %s\n", decrypted_name);
        g_print("Decrypted Password: %s\n", decrypted_password);
    }*/
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
    GtkWidget *pass_entry, *name_entry;
    GtkWidget *generate_button;
    GtkWidget *type_combo_box;

    // Створюємо блоки для пароля, типу та імені
    pass_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    type_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    name_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // Створюємо мітки для полів пароля, типу та імені
    type_label = gtk_label_new("Тип");
    name_label = gtk_label_new("Ім'я");
    pass_label = gtk_label_new("Пароль");

    // Створюємо поля вводу для пароля, типу та імені
    //type_entry = gtk_entry_new();
    //entries[0] = type_entry;
    name_entry = gtk_entry_new();
    entries[1] = name_entry;
    pass_entry = gtk_entry_new();
    gtk_widget_set_hexpand(pass_entry, TRUE);
    entries[2] = pass_entry;
    
    // Створення моделі для випадаючого списку
    GtkListStore *list_store = gtk_list_store_new(1, G_TYPE_STRING);

    // Додавання елементів до моделі
    GtkTreeIter iter;
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, 0, "Вхід", -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, 0, "Банк", -1);
    gtk_list_store_append(list_store, &iter);
    gtk_list_store_set(list_store, &iter, 0, "Інші", -1);

    // Створення випадаючого списку
    type_combo_box = gtk_combo_box_new_with_model(GTK_TREE_MODEL(list_store));
    GtkCellRenderer *renderer = gtk_cell_renderer_text_new();
    gtk_cell_layout_pack_start(GTK_CELL_LAYOUT(type_combo_box), renderer, TRUE);
    gtk_cell_layout_set_attributes(GTK_CELL_LAYOUT(type_combo_box), renderer, "text", 0, NULL);
    entries[0] = type_combo_box;

    // Створюємо кнопку "Генерувати"
    generate_button = gtk_button_new();
    GtkWidget *image = gtk_image_new_from_file("img/refresh.png");

    // Встановлюємо картинку як дочірній віджет для кнопки
    gtk_button_set_child(GTK_BUTTON(generate_button), image);

    g_signal_connect(generate_button, "clicked", G_CALLBACK(generate_button_clicked), pass_entry);

    // Додаємо мітки та поля вводу в блоки
    gtk_box_append(GTK_BOX(type_box), type_label);
    gtk_box_append(GTK_BOX(type_box), type_combo_box);

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
