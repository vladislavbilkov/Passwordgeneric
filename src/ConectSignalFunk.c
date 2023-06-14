#include "ConectSignalFunk.h"

static gboolean is_number_active = FALSE;
static gboolean is_special_active = FALSE;
static gboolean is_upper_active = FALSE;
static gboolean is_lower_active = FALSE;

static int min_numb = 1;
static int min_special = 1;
static int length = 4;

extern GtkWidget *entries[3];
extern GtkWidget *container_box;
extern GtkWidget *counters[3];

gchar *generate_pass() {
    GString *password = g_string_new("");

    if (is_number_active) {
        for (int i = 0; i < min_numb; i++) {
            gchar digit = g_random_int_range('0', '9' + 1);
            g_string_append_c(password, digit);
        }
    }

    if (is_special_active) {
        const gchar *special_chars = "!@#$%^&*()";
        int special_chars_count = strlen(special_chars);
        
        for (int i = 0; i < min_special; i++) {
            int random_index = g_random_int_range(0, special_chars_count);
            gchar special_char = special_chars[random_index];
            g_string_append_c(password, special_char);
        }
    }

    int remaining_length = length - password->len;

    if (remaining_length > 0) {
        gchar *character_set = "";

        if (is_upper_active)
            character_set = g_strconcat(character_set, "ABCDEFGHIJKLMNOPQRSTUVWXYZ", NULL);

        if (is_lower_active)
            character_set = g_strconcat(character_set, "abcdefghijklmnopqrstuvwxyz", NULL);

        if (is_number_active)
            character_set = g_strconcat(character_set, "0123456789", NULL);

        if (is_special_active)
            character_set = g_strconcat(character_set, "!@#$%^&*()", NULL);

        int character_set_length = strlen(character_set);

        for (int i = 0; i < remaining_length; i++) {
            int random_index = g_random_int_range(0, character_set_length);
            gchar random_char = character_set[random_index];
            g_string_append_c(password, random_char);
        }

        g_free(character_set);
    }

    gchar *result = g_string_free(password, FALSE);
    return result;
}

void on_scale_value_changed(GtkRange *range, GtkWidget *length_scale_label)
{
    double value = gtk_range_get_value(range);
    char buffer[10];
    sprintf(buffer, "%.0f", value);
    gtk_label_set_text(GTK_LABEL(length_scale_label), buffer);
    length = value;

    const gchar *text = generate_pass();

    GtkEntryBuffer *buffer_pass = gtk_entry_get_buffer(GTK_ENTRY(entries[2]));
    gtk_entry_buffer_set_text(buffer_pass, text, -1);
}

gboolean on_number_checkbutton_press_event(GtkWidget *widget, GtkWidget *box)
{    
    gboolean is_active = gtk_check_button_get_active(GTK_CHECK_BUTTON(widget));
    if(is_active == FALSE)
    {
        gtk_widget_set_sensitive(box, FALSE); // Встановлюємо контейнер як неактивний
    }
    else
    {
        gtk_widget_set_sensitive(box, TRUE); // Встановлюємо контейнер як активний
    }
    
    is_number_active = is_active;

    const gchar *text = generate_pass();

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entries[2]));
    gtk_entry_buffer_set_text(buffer, text, -1);

    return TRUE; // Повертаємо TRUE, щоб зупинити подальку обробку події
}

gboolean on_special_checkbutton_press_event(GtkWidget *widget, GtkWidget *box)
{    
    gboolean is_active = gtk_check_button_get_active(GTK_CHECK_BUTTON(widget));
    if(is_active == FALSE)
    {
        gtk_widget_set_sensitive(box, FALSE); // Встановлюємо контейнер як неактивний
    }
    else
    {
        gtk_widget_set_sensitive(box, TRUE); // Встановлюємо контейнер як активний
    }

    is_special_active = is_active;

    const gchar *text = generate_pass();

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entries[2]));
    gtk_entry_buffer_set_text(buffer, text, -1);

    return TRUE; // Повертаємо TRUE, щоб зупинити подальку обробку події
}

gboolean on_lower_checkbutton_press_event(GtkWidget *widget, gpointer user_data)
{
    is_lower_active = gtk_check_button_get_active(GTK_CHECK_BUTTON(widget));

    const gchar *text = generate_pass();

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entries[2]));
    gtk_entry_buffer_set_text(buffer, text, -1);

    return TRUE;
}

gboolean on_upper_checkbutton_press_event(GtkWidget *widget, gpointer user_data)
{
    is_upper_active = gtk_check_button_get_active(GTK_CHECK_BUTTON(widget));

    const gchar *text = generate_pass();

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entries[2]));
    gtk_entry_buffer_set_text(buffer, text, -1);

    return true;
}

void generate_button_clicked(GtkButton *button, gpointer user_data)
{
    const gchar *text = generate_pass();

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(entries[2]));
    gtk_entry_buffer_set_text(buffer, text, -1);
}

void on_plus_min_number_button_clicked(GtkButton *button, GtkWidget *label)
{
    if(is_special_active == TRUE)
    {
        if(min_numb + min_special > length)
        {
            gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
            return;
        }
    }
    else if(min_numb+1 > length)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
        return;
    }

    min_numb++;

    char buffer[10];
    sprintf(buffer, "%.0d", min_numb);
    gtk_label_set_text(GTK_LABEL(label), buffer);
    
}

void on_minus_min_number_button_clicked(GtkButton *button, GtkWidget *label)
{
    if(min_numb - 1 < 0)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
        return;
    }

    min_numb--;
    
    char buffer[10];
    sprintf(buffer, "%.0d", min_numb);
    gtk_label_set_text(GTK_LABEL(label), buffer);
}

void on_plus_special_button_clicked(GtkButton *button, GtkWidget *label)
{
    if(is_number_active == TRUE)
    {
        if(min_numb + min_special > length)
        {
            gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
            return;
        }
    }
    else if(min_special+1 > length)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
        return;
    }

    min_special++;
    
    char buffer[10];
    sprintf(buffer, "%.0d", min_special);
    gtk_label_set_text(GTK_LABEL(label), buffer);
}

void on_minus_special_button_clicked(GtkButton *button, GtkWidget *label)
{
    if(min_special - 1 < 0)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
        return;
    }

    min_special--;
    
    char buffer[10];
    sprintf(buffer, "%.0d", min_special);
    gtk_label_set_text(GTK_LABEL(label), buffer);
}

void login_button_clicked(GtkButton *button, GtkWidget *passentry)
{
    GtkEntryBuffer *passbufer = gtk_entry_get_buffer(GTK_ENTRY(passentry));
    const char *password = gtk_entry_buffer_get_text(passbufer);

    // Зчитування зашифрованого паролю з файлу
    FILE *file = fopen("bin/encrypted_login.bin", "rb");
    char encrypted_password[AES_BLOCK_SIZE];
    if (file != NULL) {
        fread(encrypted_password, sizeof(char), AES_BLOCK_SIZE, file);
        fclose(file);
    }
    // Розшифрування зашифрованого паролю
    char decrypted_password[AES_BLOCK_SIZE];
    const char *key = "my_secret_key";
    aes_decrypt(encrypted_password, key, decrypted_password);

    // Порівняння введеного паролю з розшифрованим паролем
    //if (strcmp(password, decrypted_password) == 0)
    if(true){
        //todo in the help ui
        GtkWidget *container = gtk_widget_get_parent(passentry);
        GtkWidget *window = gtk_widget_get_parent(container);
        GtkApplication *app = gtk_window_get_application(GTK_WINDOW(window));
        gtk_window_destroy(GTK_WINDOW(window));      
    
        content_main_window(app);
    }
}

void add_button_clicked(GtkButton *button, gpointer user_data)
{
    //todo inthe help ui
    GtkWidget *window;
    GtkWidget *container, *header_box, *propertiespass_box;
    GtkWidget *submit_button;

    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Створити новий пароль");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    // Створюємо контейнер та блоки для заголовка та властивостей пароля
    container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    header_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    propertiespass_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    // Додаємо блоки до контейнера
    gtk_box_append(GTK_BOX(container), header_box);
    gtk_box_append(GTK_BOX(container), propertiespass_box);

    // Додаємо блоки заголовка та властивостей пароля
    content_add_pass_header_box(header_box);
    content_add_pass_properties_pass_box(propertiespass_box);

    // Створюємо кнопку "Створити"
    submit_button = gtk_button_new_with_label("Створити");
    g_signal_connect(submit_button, "clicked", G_CALLBACK(on_add_pass_button_clicked), NULL);
    
    gtk_box_append(GTK_BOX(container), submit_button);

    // Встановлюємо контейнер як дочірній віджет для вікна та відображаємо вікно
    gtk_window_set_child(GTK_WINDOW(window), container);
    gtk_window_present(GTK_WINDOW(window));
}

void add_new_user_label_clicked(GtkLabel *label, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *container;
    GtkWidget *pass_label;
    GtkWidget *pass_entry;
    GtkWidget *create_button;

    window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), "Ствоерення нового акаунту");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);

    pass_label = gtk_label_new("Придумайте пароль для вашого акаунту від 5 до 20 символів\n(Постарайтесь його не забути, тому що ви можете втратити ваші дані)");

    pass_entry = gtk_entry_new();

    create_button = gtk_button_new_with_label("Створити акаунт");
    g_signal_connect(create_button, "clicked", G_CALLBACK(check_password_length), pass_entry);

    gtk_box_append(GTK_BOX(container), pass_label);
    gtk_box_append(GTK_BOX(container), pass_entry);
    gtk_box_append(GTK_BOX(container), create_button);

    gtk_window_set_child(GTK_WINDOW(window), container);
    gtk_window_present(GTK_WINDOW(window));
}

void check_password_length(GtkWidget *button, GtkWidget *passentry)
{
    GtkEntryBuffer *passbufer = gtk_entry_get_buffer(GTK_ENTRY(passentry));
    const char *password = gtk_entry_buffer_get_text(passbufer);
    int length = strlen(password);

    if (length >= 5 && length <= 20) {
        // Шифрування паролю, якщо він відповідає вимогам довжини
        char encrypted_password[AES_BLOCK_SIZE];
        const char *key = "my_secret_key";
        aes_encrypt(password, key, encrypted_password);

        FILE *file = fopen("bin/encrypted_login.bin", "wb");
        if (file != NULL) {
            fwrite(encrypted_password, sizeof(char), AES_BLOCK_SIZE, file);
            fclose(file);
        }
    } else {
        g_print("Пароль повинен мати від 5 до 20 символів.\n");
    }
}

// Функція шифрування AES
void aes_encrypt(const char *input, const char *key, char *output)
{
    AES_KEY aes_key;
    AES_set_encrypt_key((const unsigned char *)key, 128, &aes_key);
    AES_encrypt((const unsigned char *)input, (unsigned char *)output, &aes_key);
}

// Функція дешифрування AES
void aes_decrypt(const char *input, const char *key, char *output)
{
    AES_KEY aes_key;
    AES_set_decrypt_key((const unsigned char *)key, 128, &aes_key);
    AES_decrypt((const unsigned char *)input, (unsigned char *)output, &aes_key);
}

void on_add_pass_button_clicked(GtkButton *button, gpointer user_data)
{
    // Отримання тексту з полів вводу
    const char *type_text;
    GtkTreeIter iter;
    GtkTreeModel *model = gtk_combo_box_get_model(entries[0]);
    if (gtk_combo_box_get_active_iter(entries[0], &iter)) {
        gtk_tree_model_get(model, &iter, 0, &type_text, -1);
    }

    //const char *type_text = gtk_editable_get_text(GTK_EDITABLE(entries[0]));
    const char *name_text = gtk_editable_get_text(GTK_EDITABLE(entries[1]));
    const char *pass_text = gtk_editable_get_text(GTK_EDITABLE(entries[2]));

    /*const char *key = "my_secret_key";

    // Шифрування тексту
    char encrypted_type[AES_BLOCK_SIZE];
    char encrypted_name[AES_BLOCK_SIZE];
    char encrypted_password[AES_BLOCK_SIZE];

    aes_encrypt(type_text, key, encrypted_type);
    aes_encrypt(name_text, key, encrypted_name);
    aes_encrypt(pass_text, key, encrypted_password);
    
    // Запис зашифрованих даних у файл
    FILE *file = fopen("bin/encrypted_passwords.bin", "wb");
    if (file != NULL) {
        fwrite(encrypted_type, sizeof(char), AES_BLOCK_SIZE, file);
        fwrite(encrypted_name, sizeof(char), AES_BLOCK_SIZE, file);
        fwrite(encrypted_password, sizeof(char), AES_BLOCK_SIZE, file);
        fclose(file);
    }
    g_print("Just text\n");
    g_print("Type: %s\n", type_text);
    g_print("Name: %s\n", name_text);
    g_print("Password: %s\n", pass_text);

    g_print("Crypted text----\n");
    g_print("Crypted Type: %s\n", encrypted_type);
    g_print("Crypted Name: %s\n", encrypted_name);
    g_print("Crypted Password: %s\n", encrypted_password);*/

    FILE *file = fopen("bin/encrypted_passwords.bin", "ab");
    if (file != NULL) {
        size_t type_len = strlen(type_text) + 1;  // +1 для нуль-термінатора
        size_t name_len = strlen(name_text) + 1;
        size_t pass_len = strlen(pass_text) + 1;

        fwrite(&type_len, sizeof(size_t), 1, file);
        fwrite(&name_len, sizeof(size_t), 1, file);
        fwrite(&pass_len, sizeof(size_t), 1, file);
        fwrite(type_text, sizeof(char), type_len, file);
        fwrite(name_text, sizeof(char), name_len, file);
        fwrite(pass_text, sizeof(char), pass_len, file);
        
        fclose(file);
    }

    // Створення горизонтального контейнера для кожного елементу
    GtkWidget *item_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_box_set_homogeneous(GTK_BOX(item_box), TRUE);
    gtk_box_append(GTK_BOX(container_box), item_box);

    // Створення кнопки з іменем
    GtkWidget *button_pass = gtk_button_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    // Визначення типу та вибір відповідної картинки
    GtkWidget *image = NULL;

    if (strcmp(type_text, "Вхід") == 0) {
        image = gtk_image_new_from_file("img/global.png");
        // Отримання тексту з мітки
        char *text = gtk_label_get_text(GTK_LABEL(counters[0]));

        // Конвертування тексту в ціле число
        int value = atoi(text);

        sprintf(text, "%d", value + 1);
        gtk_label_set_text(GTK_LABEL(counters[0]), text);

    } else if (strcmp(type_text, "Банк") == 0) {
        image = gtk_image_new_from_file("img/credit-card.png");
        // Отримання тексту з мітки
        char *text = gtk_label_get_text(GTK_LABEL(counters[1]));

        // Конвертування тексту в ціле число
        int value = atoi(text);

        sprintf(text, "%d", value + 1);
        gtk_label_set_text(GTK_LABEL(counters[1]), text);
    } else if(strcmp(type_text, "Інші") == 0) {
        image = gtk_image_new_from_file("img/card.png");
        // Отримання тексту з мітки
        char *text = gtk_label_get_text(GTK_LABEL(counters[2]));

        // Конвертування тексту в ціле число
        int value = atoi(text);

        sprintf(text, "%d", value + 1);
        gtk_label_set_text(GTK_LABEL(counters[2]), text);
    }

    gtk_box_append(GTK_BOX(box), image);

    // Створення етикетки з іменем
    GtkWidget *name_label = gtk_label_new(name_text);
    gtk_box_append(GTK_BOX(box), name_label);

    // Додавання вертикального контейнера до кнопки
    gtk_button_set_child(GTK_BUTTON(button_pass), box);

    g_signal_connect(button_pass, "clicked", G_CALLBACK(button_item_clicked), item_box);
    gtk_box_append(GTK_BOX(item_box), button_pass);

    // Створення етикетки для паролю (початково прихована)

    char password_text[256];
    snprintf(password_text, sizeof(password_text), "Пароль: %s", pass_text);

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

    GtkWidget *toplevel = gtk_widget_get_ancestor(button, GTK_TYPE_WINDOW);

    if (GTK_IS_WINDOW(toplevel)) {
        gtk_window_close(GTK_WINDOW(toplevel));
    }

}

void button_item_clicked(GtkButton *button, gpointer user_data) {
    GtkBox *box = GTK_BOX(user_data);

    // Отримання першого дочірнього елемента контейнера
    GtkWidget *child = gtk_widget_get_last_child(GTK_WIDGET(box));

    // Отримання передостаннього дочірнього елемента контейнера
    GtkWidget *prev_sibling = gtk_widget_get_prev_sibling(child);

    // Перевірка стану видимості другого дочірнього елемента
    gboolean visible = gtk_widget_get_visible(child);

    if (visible) {
        // Приховуємо другий дочірній елемент
        gtk_widget_hide(child);
        gtk_widget_hide(prev_sibling);
    } else {
        // Показуємо другий дочірній елемент
        gtk_widget_show(child);
        gtk_widget_show(prev_sibling);
    }
}

