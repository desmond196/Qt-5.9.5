#ifndef QT_WAYLAND_SERVER_TEXT_INPUT_UNSTABLE_V2
#define QT_WAYLAND_SERVER_TEXT_INPUT_UNSTABLE_V2

#include "wayland-server.h"
#include <QtWaylandCompositor/private/wayland-text-input-unstable-v2-server-protocol.h>
#include <QByteArray>
#include <QMultiMap>
#include <QString>

#ifndef WAYLAND_VERSION_CHECK
#define WAYLAND_VERSION_CHECK(major, minor, micro) \
    ((WAYLAND_VERSION_MAJOR > (major)) || \
    (WAYLAND_VERSION_MAJOR == (major) && WAYLAND_VERSION_MINOR > (minor)) || \
    (WAYLAND_VERSION_MAJOR == (major) && WAYLAND_VERSION_MINOR == (minor) && WAYLAND_VERSION_MICRO >= (micro)))
#endif

QT_BEGIN_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_GCC("-Wmissing-field-initializers")

#if !defined(Q_WAYLAND_SERVER_TEXT_INPUT_UNSTABLE_V2_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_SERVER_TEXT_INPUT_UNSTABLE_V2_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_SERVER_TEXT_INPUT_UNSTABLE_V2_EXPORT
#  endif
#endif

namespace QtWaylandServer {
    class Q_WAYLAND_SERVER_TEXT_INPUT_UNSTABLE_V2_EXPORT zwp_text_input_v2
    {
    public:
        zwp_text_input_v2(struct ::wl_client *client, int id, int version);
        zwp_text_input_v2(struct ::wl_display *display, int version);
        zwp_text_input_v2(struct ::wl_resource *resource);
        zwp_text_input_v2();

        virtual ~zwp_text_input_v2();

        class Resource
        {
        public:
            Resource() : zwp_text_input_v2_object(0), handle(0) {}
            virtual ~Resource() {}

            zwp_text_input_v2 *zwp_text_input_v2_object;
            struct ::wl_resource *handle;

            struct ::wl_client *client() const { return handle->client; }
            int version() const { return wl_resource_get_version(handle); }

            static Resource *fromResource(struct ::wl_resource *resource);
        };

        void init(struct ::wl_client *client, int id, int version);
        void init(struct ::wl_display *display, int version);
        void init(struct ::wl_resource *resource);

        Resource *add(struct ::wl_client *client, int version);
        Resource *add(struct ::wl_client *client, int id, int version);
        Resource *add(struct wl_list *resource_list, struct ::wl_client *client, int id, int version);

        Resource *resource() { return m_resource; }
        const Resource *resource() const { return m_resource; }

        QMultiMap<struct ::wl_client*, Resource*> resourceMap() { return m_resource_map; }
        const QMultiMap<struct ::wl_client*, Resource*> resourceMap() const { return m_resource_map; }

        bool isGlobal() const { return m_global != 0; }
        bool isResource() const { return m_resource != 0; }

        static const struct ::wl_interface *interface();
        static QByteArray interfaceName() { return interface()->name; }
        static int interfaceVersion() { return interface()->version; }


        enum content_hint {
            content_hint_none = 0x0, // no special behaviour
            content_hint_auto_completion = 0x1, // suggest word completions
            content_hint_auto_correction = 0x2, // suggest word corrections
            content_hint_auto_capitalization = 0x4, // switch to uppercase letters at the start of a sentence
            content_hint_lowercase = 0x8, // prefer lowercase letters
            content_hint_uppercase = 0x10, // prefer uppercase letters
            content_hint_titlecase = 0x20, // prefer casing for titles and headings (can be language dependent)
            content_hint_hidden_text = 0x40, // characters should be hidden
            content_hint_sensitive_data = 0x80, // typed text should not be stored
            content_hint_latin = 0x100, // just latin characters should be entered
            content_hint_multiline = 0x200 // the text input is multiline
        };

        enum content_purpose {
            content_purpose_normal = 0, // default input, allowing all characters
            content_purpose_alpha = 1, // allow only alphabetic characters
            content_purpose_digits = 2, // allow only digits
            content_purpose_number = 3, // input a number (including decimal separator and sign)
            content_purpose_phone = 4, // input a phone number
            content_purpose_url = 5, // input an URL
            content_purpose_email = 6, // input an email address
            content_purpose_name = 7, // input a name of a person
            content_purpose_password = 8, // input a password (combine with password or sensitive_data hint)
            content_purpose_date = 9, // input a date
            content_purpose_time = 10, // input a time
            content_purpose_datetime = 11, // input a date and time
            content_purpose_terminal = 12 // input for a terminal
        };

        enum update_state {
            update_state_change = 0, // updated state because it changed
            update_state_full = 1, // full state after enter or input_method_changed event
            update_state_reset = 2, // full state after reset
            update_state_enter = 3 // full state after switching focus to a different widget on client side
        };

        enum input_panel_visibility {
            input_panel_visibility_hidden = 0, // the input panel (virtual keyboard) is hidden
            input_panel_visibility_visible = 1 // the input panel (virtual keyboard) is visible
        };

        enum preedit_style {
            preedit_style_default = 0, // default style for composing text
            preedit_style_none = 1, // composing text should be shown the same as non-composing text
            preedit_style_active = 2, // composing text might be bold
            preedit_style_inactive = 3, // composing text might be cursive
            preedit_style_highlight = 4, // composing text might have a different background color
            preedit_style_underline = 5, // composing text might be underlined
            preedit_style_selection = 6, // composing text should be shown the same as selected text
            preedit_style_incorrect = 7 // composing text might be underlined with a red wavy line
        };

        enum text_direction {
            text_direction_auto = 0, // automatic text direction based on text and language
            text_direction_ltr = 1, // left-to-right
            text_direction_rtl = 2 // right-to-left
        };

        void send_enter(uint32_t serial, struct ::wl_resource *surface);
        void send_enter(struct ::wl_resource *resource, uint32_t serial, struct ::wl_resource *surface);
        void send_leave(uint32_t serial, struct ::wl_resource *surface);
        void send_leave(struct ::wl_resource *resource, uint32_t serial, struct ::wl_resource *surface);
        void send_input_panel_state(uint32_t state, int32_t x, int32_t y, int32_t width, int32_t height);
        void send_input_panel_state(struct ::wl_resource *resource, uint32_t state, int32_t x, int32_t y, int32_t width, int32_t height);
        void send_preedit_string(const QString &text, const QString &commit);
        void send_preedit_string(struct ::wl_resource *resource, const QString &text, const QString &commit);
        void send_preedit_styling(uint32_t index, uint32_t length, uint32_t style);
        void send_preedit_styling(struct ::wl_resource *resource, uint32_t index, uint32_t length, uint32_t style);
        void send_preedit_cursor(int32_t index);
        void send_preedit_cursor(struct ::wl_resource *resource, int32_t index);
        void send_commit_string(const QString &text);
        void send_commit_string(struct ::wl_resource *resource, const QString &text);
        void send_cursor_position(int32_t index, int32_t anchor);
        void send_cursor_position(struct ::wl_resource *resource, int32_t index, int32_t anchor);
        void send_delete_surrounding_text(uint32_t before_length, uint32_t after_length);
        void send_delete_surrounding_text(struct ::wl_resource *resource, uint32_t before_length, uint32_t after_length);
        void send_modifiers_map(const QByteArray &map);
        void send_modifiers_map(struct ::wl_resource *resource, const QByteArray &map);
        void send_keysym(uint32_t time, uint32_t sym, uint32_t state, uint32_t modifiers);
        void send_keysym(struct ::wl_resource *resource, uint32_t time, uint32_t sym, uint32_t state, uint32_t modifiers);
        void send_language(const QString &language);
        void send_language(struct ::wl_resource *resource, const QString &language);
        void send_text_direction(uint32_t direction);
        void send_text_direction(struct ::wl_resource *resource, uint32_t direction);
        void send_configure_surrounding_text(int32_t before_cursor, int32_t after_cursor);
        void send_configure_surrounding_text(struct ::wl_resource *resource, int32_t before_cursor, int32_t after_cursor);
        void send_input_method_changed(uint32_t serial, uint32_t flags);
        void send_input_method_changed(struct ::wl_resource *resource, uint32_t serial, uint32_t flags);

    protected:
        virtual Resource *zwp_text_input_v2_allocate();

        virtual void zwp_text_input_v2_bind_resource(Resource *resource);
        virtual void zwp_text_input_v2_destroy_resource(Resource *resource);

        virtual void zwp_text_input_v2_destroy(Resource *resource);
        virtual void zwp_text_input_v2_enable(Resource *resource, struct ::wl_resource *surface);
        virtual void zwp_text_input_v2_disable(Resource *resource, struct ::wl_resource *surface);
        virtual void zwp_text_input_v2_show_input_panel(Resource *resource);
        virtual void zwp_text_input_v2_hide_input_panel(Resource *resource);
        virtual void zwp_text_input_v2_set_surrounding_text(Resource *resource, const QString &text, int32_t cursor, int32_t anchor);
        virtual void zwp_text_input_v2_set_content_type(Resource *resource, uint32_t hint, uint32_t purpose);
        virtual void zwp_text_input_v2_set_cursor_rectangle(Resource *resource, int32_t x, int32_t y, int32_t width, int32_t height);
        virtual void zwp_text_input_v2_set_preferred_language(Resource *resource, const QString &language);
        virtual void zwp_text_input_v2_update_state(Resource *resource, uint32_t serial, uint32_t reason);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::zwp_text_input_v2_interface m_zwp_text_input_v2_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_enable(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *surface);
        static void handle_disable(
            ::wl_client *client,
            struct wl_resource *resource,
            struct ::wl_resource *surface);
        static void handle_show_input_panel(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_hide_input_panel(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_set_surrounding_text(
            ::wl_client *client,
            struct wl_resource *resource,
            const char *text,
            int32_t cursor,
            int32_t anchor);
        static void handle_set_content_type(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t hint,
            uint32_t purpose);
        static void handle_set_cursor_rectangle(
            ::wl_client *client,
            struct wl_resource *resource,
            int32_t x,
            int32_t y,
            int32_t width,
            int32_t height);
        static void handle_set_preferred_language(
            ::wl_client *client,
            struct wl_resource *resource,
            const char *language);
        static void handle_update_state(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t serial,
            uint32_t reason);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };

    class Q_WAYLAND_SERVER_TEXT_INPUT_UNSTABLE_V2_EXPORT zwp_text_input_manager_v2
    {
    public:
        zwp_text_input_manager_v2(struct ::wl_client *client, int id, int version);
        zwp_text_input_manager_v2(struct ::wl_display *display, int version);
        zwp_text_input_manager_v2(struct ::wl_resource *resource);
        zwp_text_input_manager_v2();

        virtual ~zwp_text_input_manager_v2();

        class Resource
        {
        public:
            Resource() : zwp_text_input_manager_v2_object(0), handle(0) {}
            virtual ~Resource() {}

            zwp_text_input_manager_v2 *zwp_text_input_manager_v2_object;
            struct ::wl_resource *handle;

            struct ::wl_client *client() const { return handle->client; }
            int version() const { return wl_resource_get_version(handle); }

            static Resource *fromResource(struct ::wl_resource *resource);
        };

        void init(struct ::wl_client *client, int id, int version);
        void init(struct ::wl_display *display, int version);
        void init(struct ::wl_resource *resource);

        Resource *add(struct ::wl_client *client, int version);
        Resource *add(struct ::wl_client *client, int id, int version);
        Resource *add(struct wl_list *resource_list, struct ::wl_client *client, int id, int version);

        Resource *resource() { return m_resource; }
        const Resource *resource() const { return m_resource; }

        QMultiMap<struct ::wl_client*, Resource*> resourceMap() { return m_resource_map; }
        const QMultiMap<struct ::wl_client*, Resource*> resourceMap() const { return m_resource_map; }

        bool isGlobal() const { return m_global != 0; }
        bool isResource() const { return m_resource != 0; }

        static const struct ::wl_interface *interface();
        static QByteArray interfaceName() { return interface()->name; }
        static int interfaceVersion() { return interface()->version; }


    protected:
        virtual Resource *zwp_text_input_manager_v2_allocate();

        virtual void zwp_text_input_manager_v2_bind_resource(Resource *resource);
        virtual void zwp_text_input_manager_v2_destroy_resource(Resource *resource);

        virtual void zwp_text_input_manager_v2_destroy(Resource *resource);
        virtual void zwp_text_input_manager_v2_get_text_input(Resource *resource, uint32_t id, struct ::wl_resource *seat);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::zwp_text_input_manager_v2_interface m_zwp_text_input_manager_v2_interface;

        static void handle_destroy(
            ::wl_client *client,
            struct wl_resource *resource);
        static void handle_get_text_input(
            ::wl_client *client,
            struct wl_resource *resource,
            uint32_t id,
            struct ::wl_resource *seat);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };
}

QT_WARNING_POP
QT_END_NAMESPACE

#endif
