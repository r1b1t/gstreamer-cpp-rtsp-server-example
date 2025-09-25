#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>

int main(int argc, char *argv[])
{
    gst_init(&argc, &argv);

    // RTSP Server oluşturuldu
    GstRTSPServer *server = gst_rtsp_server_new();
    // RTSP port atandı. rtsp://HOST:8554/...
    gst_rtsp_server_set_service(server, "8554");

    // Mount Point'leri al
    // RTSP server’da hangi URL yoluna hangi medya kaynağının bağlanacağını yöneten yapı.
    // bir path tanımlar bu pathde factory'ye göre veriyi yansıtır
    GstRTSPMountPoints *mounts = gst_rtsp_server_get_mount_points(server);

    // Pipeline tanımı (test videosu)
    const gchar *pipeline_desc =
        "( videotestsrc is-live=true "
        "! video/x-raw,framerate=30/1,width=640,height=480 "
        "! x264enc tune=zerolatency speed-preset=ultrafast bitrate=2000 key-int-max=30 "
        "! rtph264pay name=pay0 pt=96 config-interval=1 )";

    // Media Factory oluştur, mount noktasına hangi pipeline’ın atanacağını tanımlar.
    // Factory'nin içinde pipeline tanımlıdır buna göre veriyi yansıtır.
    GstRTSPMediaFactory *factory = gst_rtsp_media_factory_new();
    gst_rtsp_media_factory_set_launch(factory, pipeline_desc);
    // aynı pipeline birden çok istemciyle paylaşılır (yani her izleyici için yeni pipeline yaratılmaz, tek kaynak olur).
    // (CPU/GPU daha az yüklenir)
    gst_rtsp_media_factory_set_shared(factory, TRUE);

    // /test'i mount noktasına ekle
    gst_rtsp_mount_points_add_factory(mounts, "/test", factory);

    g_object_unref(mounts);

    // Sunucuyu GLib main loop'a bağla
    // RTSP server’ı main loop’a bağlar.
    // Yani TCP/UDP portlarını açar, dinlemeye başlar.
    gst_rtsp_server_attach(server, NULL);

    g_print("RTSP sunucusu çalışıyor: rtsp://127.0.0.1:8554/test\n");

    // Main loop başlat, bilgileri almak için loop oluşturuyoruz
    GMainLoop *loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);

    return 0;
}
