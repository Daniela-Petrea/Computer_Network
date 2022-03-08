#include <gtk/gtk.h>
GtkWidget *label;
extern int errno;
int sd;			
char msg[100],msg2[100];		
int nr=0;
static void toggled_func(GtkWidget* widget, gpointer data)
{ 
    if(strcmp((char*)data, "1") == 0)
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
            {strcpy(msg,"S-a apasat rosu");
   if (write (sd, msg, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }         
 }
    if(strcmp((char*)data, "2") == 0)
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
           {strcpy(msg,"S-a apasat galben");            
   if (write (sd, msg, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
    }         
    if(strcmp((char*)data, "3") == 0)
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
           {strcpy(msg,"S-a apasat verde");
   if (write (sd, msg, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }         
    }
    if(strcmp((char*)data, "4") == 0)
        if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
            {strcpy(msg,"S-a apasat albastru");            
   if (write (sd, msg, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }         
   }
}
 
void button_clicked1(GtkWidget* widget, gpointer data)
{
  strcpy(msg,"S-a inchis becul nr ");
  bzero(msg2,100);
  sprintf(msg2,"%d",nr);
  strcat(msg,msg2);
  nr--;
  if (write (sd, msg, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
}
void value_changed1(GtkRange *range, gpointer win) {
   gdouble val = gtk_range_get_value(range);
   gchar *str = g_strdup_printf("%.f", val);  
  strcpy(msg,"Intensitatea este ");
  strcat(msg,str);
  if (write (sd, msg, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
   gtk_label_set_text(GTK_LABEL(win), str);
    gtk_label_set_markup(GTK_LABEL(label), str);
    PangoAttrList *attrlist = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_size_new_absolute(20 * PANGO_SCALE);
    pango_attr_list_insert(attrlist, attr);
    gtk_label_set_attributes(GTK_LABEL(label), attrlist);
    pango_attr_list_unref(attrlist);
   g_free(str);
}
void cb_create_entry1(GtkWidget *p_widget, gpointer user_data){
  nr++;
  strcpy(msg,"S-a deschis becul nr ");
  bzero(msg2,100);
  sprintf(msg2,"%d",nr);
  strcat(msg,msg2);
  if (write (sd, msg, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
    gtk_button_released(p_widget);
    GtkWidget *window,*entry,*k,*table, *button,*button1,*button2,*hscale,*label1,*label2;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window), 500, 500);
    gtk_window_set_title(GTK_WINDOW(window), "Bec");
  gchar *values[8] = { "rosu", "", 
     "galben", "",
     "verde", "",
     "albastru", ""
  };
  table = gtk_table_new(7, 4, TRUE);
   gchar *str1 = "<b>     Culoare:</b>";
   label1 = gtk_label_new(NULL); 
   gtk_label_set_markup(GTK_LABEL(label1), str1);
    PangoAttrList *attrlist1 = pango_attr_list_new();
    PangoAttribute *attr1 = pango_attr_size_new_absolute(25 * PANGO_SCALE);
    pango_attr_list_insert(attrlist1, attr1);
    gtk_label_set_attributes(GTK_LABEL(label1), attrlist1);
    pango_attr_list_unref(attrlist1); 
  int pos = 0;
  while(pos!=8){
     GdkColor color;
      if(pos==0)
      {button1 = gtk_radio_button_new_with_label(NULL,"rosu");
      gtk_widget_modify_font(button1, pango_font_description_from_string("Arial Black 18"));
       g_signal_connect(button1, "toggled", G_CALLBACK(toggled_func), (gpointer)"1");
      gtk_table_attach_defaults(GTK_TABLE(table), button1, 1, 2, 1, 2);
      }
       if(pos==1)
      {button = gtk_button_new_with_label(values[pos]);
      gdk_color_parse("red",&color);
      gtk_widget_modify_bg (GTK_WIDGET(button),GTK_STATE_NORMAL,&color);
      gtk_table_attach_defaults(GTK_TABLE(table), button, 2, 3, 1, 2);
      }
       if(pos==2)
      {
      button2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button1)), "galben");
      gtk_widget_modify_font(button2, pango_font_description_from_string("Arial Black 18"));
      g_signal_connect(button2, "toggled", G_CALLBACK(toggled_func), (gpointer)"2");
         gtk_table_attach_defaults(GTK_TABLE(table), button2, 1, 2, 2, 3);
      }
       if(pos==3)
      {button = gtk_button_new_with_label(values[pos]);
      gdk_color_parse("yellow",&color);
      gtk_widget_modify_bg (GTK_WIDGET(button),GTK_STATE_NORMAL,&color);
      gtk_table_attach_defaults(GTK_TABLE(table), button, 2, 3, 2, 3);
      }
       if(pos==4)
      {
      button2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button1)), "verde");
       gtk_widget_modify_font(button2, pango_font_description_from_string("Arial Black 18"));
       g_signal_connect(button2, "toggled", G_CALLBACK(toggled_func), (gpointer)"3");
      gtk_table_attach_defaults(GTK_TABLE(table), button2, 1, 2, 3, 4);
      }
       if(pos==5)
      {button = gtk_button_new_with_label(values[pos]);
      gdk_color_parse("green",&color);
      gtk_widget_modify_bg (GTK_WIDGET(button),GTK_STATE_NORMAL,&color);
      gtk_table_attach_defaults(GTK_TABLE(table), button, 2, 3, 3, 4);
      }
       if(pos==6)
      {button2 = gtk_radio_button_new_with_label(gtk_radio_button_get_group(GTK_RADIO_BUTTON(button1)), "albastru");
       gtk_widget_modify_font(button2, pango_font_description_from_string("Arial Black 18"));
       g_signal_connect(button2, "toggled", G_CALLBACK(toggled_func), (gpointer)"4");
      gtk_table_attach_defaults(GTK_TABLE(table), button2, 1, 2, 4, 5);
      }
       if(pos==7)
      {button = gtk_button_new_with_label(values[pos]);
      gdk_color_parse("blue",&color);
      gtk_widget_modify_bg (GTK_WIDGET(button),GTK_STATE_NORMAL,&color);
      gtk_table_attach_defaults(GTK_TABLE(table), button, 2, 3, 4, 5);
      }
      pos++;
    }
    gchar *str2 = "<b>     Intensitate:</b>";
   label2 = gtk_label_new(NULL);
   gtk_label_set_markup(GTK_LABEL(label2), str2);
    PangoAttrList *attrlist2 = pango_attr_list_new();
    PangoAttribute *attr2 = pango_attr_size_new_absolute(25 * PANGO_SCALE);
    pango_attr_list_insert(attrlist2, attr2);
    gtk_label_set_attributes(GTK_LABEL(label2), attrlist2);
    pango_attr_list_unref(attrlist2); 
  hscale = gtk_hscale_new_with_range(0, 100, 1);
  gtk_scale_set_draw_value(GTK_SCALE(hscale), FALSE);
  gtk_widget_set_size_request(hscale, 150, -1);
  label = gtk_label_new("..."); 
  gtk_misc_set_alignment(GTK_MISC(label), 0.0, 1);
  gtk_table_attach_defaults(GTK_TABLE(table), label1, 1, 2, 0, 1);
  gtk_table_attach_defaults(GTK_TABLE(table), label2, 1, 2, 5, 6);
  gtk_table_attach_defaults(GTK_TABLE(table), hscale, 0, 4, 6, 7);
  gtk_table_attach_defaults(GTK_TABLE(table), label, 3, 4, 6, 7);
  gtk_container_add(GTK_CONTAINER(window), table);
  g_signal_connect(hscale, "value-changed",  G_CALLBACK(value_changed1), label);   
  g_signal_connect(window, "destroy", G_CALLBACK(button_clicked1), NULL);
  gtk_widget_show_all(window);
}

