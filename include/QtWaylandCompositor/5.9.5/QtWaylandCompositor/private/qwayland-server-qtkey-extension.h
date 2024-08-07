#ifndef QT_WAYLAND_SERVER_QTKEY_EXTENSION
#define QT_WAYLAND_SERVER_QTKEY_EXTENSION

#include "wayland-server.h"
#include <QtWaylandCompositor/private/wayland-qtkey-extension-server-protocol.h>
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

#if !defined(Q_WAYLAND_SERVER_QTKEY_EXTENSION_EXPORT)
#  if defined(QT_SHARED)
#    define Q_WAYLAND_SERVER_QTKEY_EXTENSION_EXPORT Q_DECL_EXPORT
#  else
#    define Q_WAYLAND_SERVER_QTKEY_EXTENSION_EXPORT
#  endif
#endif

namespace QtWaylandServer {
    class Q_WAYLAND_SERVER_QTKEY_EXTENSION_EXPORT qt_key_extension
    {
    public:
        qt_key_extension(struct ::wl_client *client, int id, int version);
        qt_key_extension(struct ::wl_display *display, int version);
        qt_key_extension(struct ::wl_resource *resource);
        qt_key_extension();

        virtual ~qt_key_extension();

        class Resource
        {
        public:
            Resource() : key_extension_object(0), handle(0) {}
            virtual ~Resource() {}

            qt_key_extension *key_extension_object;
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


        void send_qtkey(struct ::wl_resource *surface, uint32_t time, uint32_t type, uint32_t key, uint32_t modifiers, uint32_t nativeScanCode, uint32_t nativeVirtualKey, uint32_t nativeModifiers, const QString &text, uint32_t autorepeat, uint32_t count);
        void send_qtkey(struct ::wl_resource *resource, struct ::wl_resource *surface, uint32_t time, uint32_t type, uint32_t key, uint32_t modifiers, uint32_t nativeScanCode, uint32_t nativeVirtualKey, uint32_t nativeModifiers, const QString &text, uint32_t autorepeat, uint32_t count);

    protected:
        virtual Resource *key_extension_allocate();

        virtual void key_extension_bind_resource(Resource *resource);
        virtual void key_extension_destroy_resource(Resource *resource);

        virtual void key_extension_dummy(Resource *resource);

    private:
        static void bind_func(struct ::wl_client *client, void *data, uint32_t version, uint32_t id);
        static void destroy_func(struct ::wl_resource *client_resource);

        Resource *bind(struct ::wl_client *client, uint32_t id, int version);
        Resource *bind(struct ::wl_resource *handle);

        static const struct ::qt_key_extension_interface m_qt_key_extension_interface;

        static void handle_dummy(
            ::wl_client *client,
            struct wl_resource *resource);

        QMultiMap<struct ::wl_client*, Resource*> m_resource_map;
        Resource *m_resource;
        struct ::wl_global *m_global;
        uint32_t m_globalVersion;
    };
}

QT_WARNING_POP
QT_END_NAMESPACE

#endif
