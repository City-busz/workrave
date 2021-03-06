// Copyright (C) 2001 - 2017 Rob Caelers & Raymond Penners
// All rights reserved.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef PRELUDEWINDOW_HH
#define PRELUDEWINDOW_HH

#include "BreakWindow.hh"
#include "IPreludeWindow.hh"

class TimeBar;
class Frame;

namespace Gtk
{
  class Image;
  class Label;
}

class PreludeWindow :
  public Gtk::Window,
  public IPreludeWindow
{
public:
  PreludeWindow(HeadInfo &head, BreakId break_id);
  virtual ~PreludeWindow();

  void start();
  void stop();
  void destroy();
  void refresh();
  void set_progress(int value, int max_value);
  void set_stage(IApp::PreludeStage stage);
  void set_progress_text(IApp::PreludeProgressText text);

private:
  void on_frame_flash_event(bool frame_visible);
  void add(Gtk::Widget& widget);

#ifdef PLATFORM_OS_WIN32
  void init_avoid_pointer_polling();
  bool on_avoid_pointer_timer_event();
#else
  bool on_enter_notify_event(GdkEventCrossing* event);
#endif
  void get_pointer_location(int &x, int &y);
  void avoid_pointer();

#ifdef HAVE_GTK3
  bool on_draw_event(const ::Cairo::RefPtr< ::Cairo::Context>& cr);
  void on_screen_changed_event(const Glib::RefPtr<Gdk::Screen>& previous_screen);
  void update_input_region(Gtk::Allocation &allocation);
  void on_size_allocate_event(Gtk::Allocation &allocation);
#endif

private:
#ifdef PLATFORM_OS_WIN32
  //! Avoid time signal
  sigc::connection avoid_signal;

  int gdk_offset_x;
  int gdk_offset_y;
#endif

  //! Avoid margin.
  const int SCREEN_MARGIN;

  //! Did we avoid the pointer?
  bool did_avoid;

  //! Time bar
  TimeBar *time_bar;

  //! Frame
  Frame *frame;

  //! Frame
  Frame *window_frame;

  //! Warn color
  Gdk::Color color_warn;

  //! Alert color
  Gdk::Color color_alert;

  //! Label
  Gtk::Label *label;

  //! Icon
  Gtk::Image *image_icon;

  //! Final prelude
  std::string progress_text;

  //! Progress values
  int progress_value;
  int progress_max_value;

  //! Flash
  bool flash_visible;

  //! Head
  HeadInfo head;

  // Aligment in Waylang
  Gtk::Alignment *align;
};

#endif // PRELUDEWINDOW_HH
