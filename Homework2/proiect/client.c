#include <gtk/gtk.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include "bec.h"
#include "telecomanda.h"
#include "ac.h"
extern int errno;
int port;
int sd;
char msg[100],msg2[100];				
struct sockaddr_in server;	
static void destroy(GtkWidget *widget, gpointer data)
{ 
  strcpy(msg,"S-a inchis clientul ");
  if (write (sd, msg, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
  close (sd);
gtk_main_quit();
}

void cb_create_entry1(GtkWidget *, gpointer);
void cb_create_entry2(GtkWidget *, gpointer);
void cb_create_entry3(GtkWidget *, gpointer);
int create_window(int argc, char *argv[]){
   GtkWidget *window = NULL;
   GtkWidget *main_box = NULL;
   GtkWidget *button[3];
   GtkWidget *label;
   gtk_init (&argc, &argv);
   window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   gtk_window_set_title(GTK_WINDOW(window), "IoT Simulator");
   gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
   g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);
   main_box = gtk_vbox_new(TRUE, 0);
   gtk_container_add(GTK_CONTAINER(window), main_box);
   gchar *str = "<b>IoT Simulator</b>";
   label = gtk_label_new(NULL);
   gtk_label_set_markup(GTK_LABEL(label), str);
    PangoAttrList *attrlist = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_size_new_absolute(40 * PANGO_SCALE);
    pango_attr_list_insert(attrlist, attr);
    gtk_label_set_attributes(GTK_LABEL(label), attrlist);
    pango_attr_list_unref(attrlist);  
   gtk_box_pack_start(GTK_BOX(main_box), label, FALSE, FALSE, 0);
   gtk_widget_show(label);
   button[0] = gtk_button_new_with_label(" Bec");
   GtkWidget *image1 = gtk_image_new_from_file ("/home/daniela/proiect/lightbulb.png");
   gtk_button_set_always_show_image (GTK_BUTTON (button[0]), TRUE);
   gtk_button_set_image (GTK_BUTTON (button[0]), image1);
   gtk_widget_modify_font(button[0], pango_font_description_from_string("Arial Black 18"));
   g_signal_connect(G_OBJECT(button[0]), "clicked", G_CALLBACK(cb_create_entry1), NULL);
   gtk_box_pack_start(GTK_BOX(main_box), button[0], TRUE, TRUE, 1);
   button[1] = gtk_button_new_with_label(" Telecomanda TV");
   GtkWidget *image2 = gtk_image_new_from_file ("/home/daniela/proiect/remote-control.png");
   gtk_button_set_always_show_image (GTK_BUTTON (button[1]), TRUE);
   gtk_button_set_image (GTK_BUTTON (button[1]), image2);
   gtk_widget_modify_font(button[1], pango_font_description_from_string("Arial Black 18"));
   g_signal_connect(G_OBJECT(button[1]), "clicked",  G_CALLBACK(cb_create_entry2), NULL);
   gtk_box_pack_start(GTK_BOX(main_box), button[1], TRUE, TRUE, 1);
   button[2] = gtk_button_new_with_label("  Aer conditionat");
   GtkWidget *image3 = gtk_image_new_from_file ("/home/daniela/proiect/air-conditioner.png");
   gtk_button_set_always_show_image (GTK_BUTTON (button[2]), TRUE);
   gtk_button_set_image (GTK_BUTTON (button[2]), image3);
   gtk_widget_modify_font(button[2], pango_font_description_from_string("Arial Black 18"));
   g_signal_connect(G_OBJECT(button[2]), "clicked",  G_CALLBACK(cb_create_entry3), NULL);
   gtk_box_pack_start(GTK_BOX(main_box), button[2], TRUE, TRUE, 1);
   gtk_widget_show_all(window);
}

int main (int argc, char *argv[]) {
  if (argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }
  port = atoi (argv[2]);
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  server.sin_port = htons (port);
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }
   create_window(argc, argv);
   gtk_main ();
   return 0;
}

