#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#define NUM_POINTS 100

// Generate a simple data set (sine wave)
void generate_data(FILE *file) {
    double x, y;
    for (int i = 0; i < NUM_POINTS; ++i) {
        x = i * 2 * M_PI / NUM_POINTS;
        y = sin(x);
        fprintf(file, "%lf %lf\n", x, y);
    }
}

// Callback function for closing the window
void close_window(GtkWidget *widget, gpointer data) {
    gtk_main_quit();
}

int main(int argc, char *argv[]) {
    // Generate data
    FILE *dataFile = fopen("data.txt", "w");
    if (!dataFile) {
        printf("Error opening data file\n");
        return 1;
    }
    generate_data(dataFile);
    fclose(dataFile);

    // Generate plot using Gnuplot
    FILE *gnuplotPipe = popen("gnuplot -persist", "w");
    if (!gnuplotPipe) {
        printf("Error opening pipe to Gnuplot\n");
        return 1;
    }
    fprintf(gnuplotPipe, "set terminal png\n");
    fprintf(gnuplotPipe, "set output 'plot.png'\n");
    fprintf(gnuplotPipe, "plot 'data.txt' with lines\n");
    fflush(gnuplotPipe);
    fprintf(gnuplotPipe, "exit\n");
    pclose(gnuplotPipe);

    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create the main window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Gnuplot Plot in GUI");
    g_signal_connect(window, "destroy", G_CALLBACK(close_window), NULL);

    // Create an image widget
    GtkWidget *image = gtk_image_new_from_file("plot.png");

    // Add the image widget to the window
    gtk_container_add(GTK_CONTAINER(window), image);

    // Set window size and show
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();

    return 0;
}
