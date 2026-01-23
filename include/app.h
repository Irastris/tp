#ifndef _APP_H_
#define _APP_H_

#include <cstdint>

#include "dolphin/vi.h"

namespace tp {
    struct Application {
        private:
            // bool m_projectInitialized = false;

        public:
            Application(){}

            bool onAppIdle() {
                /* if (!m_projectInitialized) {
                    if (CDvdFile::Initialize("game.iso")) {
                        m_projectInitialized = true;
                    }
                }

                if (!g_mainMP1 && m_projectInitialized) {
                    g_mainMP1.emplace(nullptr, nullptr);
                    auto result = g_mainMP1->Init();
                }

                if (g_mainMP1) {
                    if (g_mainMP1->Proc()) {
                        return false;
                    }
                } */

                return true;
            }

            void onAppDraw() {
                /* if (g_Renderer != nullptr) {
                    g_Renderer->BeginScene();

                    if (g_mainMP1) {
                        g_mainMP1->Draw();
                    }

                    g_Renderer->EndScene();
                } */
            }

            // TODO: Determine if this should be active
            void onAppPostDraw() {
                /* CDvdFile::DoWork();
                CGraphics::TickRenderTimings(); */
            }

            /* void onAppWindowResized(const AuroraWindowSize& size) {
                CGraphics::SetViewportResolution({static_cast<s32>(size.fb_width), static_cast<s32>(size.fb_height)});
            } */

            void onAppExiting() {
                /* if (g_mainMP1) {
                    g_mainMP1->Shutdown();
                }
                g_mainMP1.reset();
                CDvdFile::Shutdown(); */
            }
    };
} // namespace tp

#endif
