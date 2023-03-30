#include <gtk/gtk.h>
#include "funk.h"

static void click_submit_btn(GtkButton *btn, GtkWidget *box)
{
    //Оголошення потрібних зміних
    GtkWidget *tv;
    GtkWidget *text_view;
    GtkTextBuffer *tb;
    GtkTextIter start_iter;
    GtkTextIter end_iter;
    char *contents;

    //взяття тексту
    tv = gtk_widget_get_first_child(box);
    tb = gtk_text_view_get_buffer(GTK_TEXT_VIEW(tv));
    gtk_text_buffer_get_bounds(tb, &start_iter, &end_iter);
    contents = gtk_text_buffer_get_text(tb, &start_iter, &end_iter, FALSE);

    //Оголошення початкової матриці 
    int row, column;
    row = size_row(contents);
    column = size_column(contents);    
    double matr[row][column];

    initial_table(contents, row, column, matr);//заповнення матриці
    
    //ініціалізація елементу для виводу матриці
    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE); // Заборона редагування тексту
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text_view), FALSE); // Приховування курсора
    gtk_box_append(GTK_BOX(box), text_view);
    
    char buffer[256];
    GtkTextBuffer *buffer_text = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view)); // Отримання буфера тексту
    GtkTextIter iter;
    gtk_text_buffer_get_start_iter(buffer_text, &iter); // Отримання початкового ітератора буфера тексту

    sprintf(buffer, "\n\tПочаткова таблиця\n");
    gtk_text_buffer_insert(buffer_text, &iter, buffer, -1);

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            sprintf(buffer, "%.2f\t", matr[i][j]); // Форматування значення для виводу
            gtk_text_buffer_insert(buffer_text, &iter, buffer, -1); // Вставка тексту в GtkTextView
        }
        sprintf(buffer, "\n"); // Додавання символу нового рядка
        gtk_text_buffer_insert(buffer_text, &iter, buffer, -1); // Вставка тексту в GtkTextView
    }   

    while(!is_optimality(row, column, matr))//перевірка на оптимальність
    {
        calculate_next_table(row, column, matr);//розрахунок настпної матриці
        sprintf(buffer, "\n\tНаступна таблиця\n");
        gtk_text_buffer_insert(buffer_text, &iter, buffer, -1);
        //вивід на екран результату обчисленнь
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < column; j++)
            {
                sprintf(buffer, "%.2f\t", matr[i][j]); // Форматування значення для виводу
                gtk_text_buffer_insert(buffer_text, &iter, buffer, -1); // Вставка тексту в GtkTextView
            }
            sprintf(buffer, "\n"); // Додавання символу нового рядка
            gtk_text_buffer_insert(buffer_text, &iter, buffer, -1); // Вставка тексту в GtkTextView
        }   
    }
}

static void app_activate (GApplication *app, gpointer *user_data) {
    GtkWidget *win;
    GtkWidget *srcrollwindow;
    GtkWidget *box;

    GtkWidget *tv;
    GtkTextBuffer *tb;
    GtkWidget *btn;
    gchar *text;

    text = "z - 4x1 - 6x2 = 0\n2x1 + x2 + S1 = 64\nx1 + 3x2 + S2 = 72\nx2 + S3 = 20\n";

    win = gtk_application_window_new (GTK_APPLICATION (app));
    gtk_window_set_title (GTK_WINDOW (win), "test");
    gtk_window_set_default_size (GTK_WINDOW (win), 400, 300);

    srcrollwindow = gtk_scrolled_window_new();
    gtk_window_set_child(GTK_WINDOW(win), srcrollwindow);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_set_homogeneous (GTK_BOX (box), TRUE);
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(srcrollwindow), box);

    tv = gtk_text_view_new ();
    tb = gtk_text_view_get_buffer (GTK_TEXT_VIEW (tv));
    gtk_text_buffer_set_text (tb, text, -1);
    gtk_text_view_set_wrap_mode (GTK_TEXT_VIEW (tv), GTK_WRAP_WORD_CHAR);

    btn = gtk_button_new_with_label("Розрахувати");
    g_signal_connect(btn, "clicked", G_CALLBACK(click_submit_btn), box);

    gtk_box_append(GTK_BOX(box), tv);
    gtk_box_append(GTK_BOX(box), btn);

    gtk_window_present (GTK_WINDOW (win));
}

int main (int argc, char **argv) {
    GtkApplication *app;
    int stat;

    app = gtk_application_new ("com.github.ToshioCP.pr2", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect (app, "activate", G_CALLBACK (app_activate), NULL);
    stat =g_application_run (G_APPLICATION (app), argc, argv);
    g_object_unref (app);
    return stat;
}