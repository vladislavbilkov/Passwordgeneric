#include "ConectSignalFunk.h"

static gboolean is_number_active = FALSE;
static gboolean is_special_active = FALSE;
static gboolean is_upper_active = FALSE;
static gboolean is_lower_active = FALSE;

static int min_numb = 1;
static int min_special = 1;
static int length = 4;

extern GtkWidget *ptr_entry;

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

    GtkEntryBuffer *buffer_pass = gtk_entry_get_buffer(GTK_ENTRY(ptr_entry));
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

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(ptr_entry));
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

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(ptr_entry));
    gtk_entry_buffer_set_text(buffer, text, -1);

    return TRUE; // Повертаємо TRUE, щоб зупинити подальку обробку події
}

gboolean on_lower_checkbutton_press_event(GtkWidget *widget, gpointer user_data)
{
    is_lower_active = gtk_check_button_get_active(GTK_CHECK_BUTTON(widget));

    const gchar *text = generate_pass();

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(ptr_entry));
    gtk_entry_buffer_set_text(buffer, text, -1);

    return TRUE;
}

gboolean on_upper_checkbutton_press_event(GtkWidget *widget, gpointer user_data)
{
    is_upper_active = gtk_check_button_get_active(GTK_CHECK_BUTTON(widget));

    const gchar *text = generate_pass();

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(ptr_entry));
    gtk_entry_buffer_set_text(buffer, text, -1);

    return true;
}

void generate_button_clicked(GtkButton *button, gpointer user_data)
{
    const gchar *text = generate_pass();

    GtkEntryBuffer *buffer = gtk_entry_get_buffer(GTK_ENTRY(ptr_entry));
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
    const char *text = gtk_entry_buffer_get_text(passbufer);
    g_print(text);
    //read text on file
    //TODO: розгифрування
    //check pass
    if(true)
    {
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
    gtk_box_append(GTK_BOX(container), submit_button);

    // Встановлюємо контейнер як дочірній віджет для вікна та відображаємо вікно
    gtk_window_set_child(GTK_WINDOW(window), container);
    gtk_window_present(GTK_WINDOW(window));
}