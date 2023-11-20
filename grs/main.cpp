#include <iostream>

#include "burst/Engine.h"

#include "grs/MeshPresenter.h"
#include "vkt/Mesh.h"

class GearsEngine
:
    public burst::Engine
{
    public:
        GearsEngine( std::size_t inWidth, std::size_t inHeight, const char * inTitle )
        :
            burst::Engine( inWidth, inHeight, inTitle ),
            mPresenter( GetPresentContext(), std::bind( & GearsEngine::Draw, this, std::placeholders::_1 ) )
        {
            std::size_t samples = 30;
            std::vector< vkt::Vertex > vertices;
            vertices.emplace_back( glm::vec3( 0.0f, 0.0f, 0.0f ), glm::vec3(), glm::vec3( 0.0f, 1.0f, 0.0f ) );
            for( int i = 0; i < samples; i++ )
            {
                float angle = 2.0f * 3.1415926f * i / float( samples );
                vertices.emplace_back( glm::vec3( cos( angle ), sin( angle ), 0.0f ), glm::vec3(), glm::vec3( 0.0f, 1.0f, 0.0f ) );
            }
            std::vector< std::uint32_t > indices;
            for( int i = 0; i < samples; i++ )
            {
                indices.push_back( 0 );
                indices.push_back( i );
                indices.push_back( i + 1 );
            }
            indices.push_back( 0 );
            indices.push_back( 1 );
            indices.push_back( samples );
            mMesh = std::make_shared< vkt::Mesh >
            (
                GetPresentContext().mDevice,
                vertices,
                indices
            );

        }

        ~GearsEngine()
        {
            GetPresentContext().mDevice.GetVkDevice().waitIdle();
        }

        void Draw( vk::CommandBuffer inCommandBuffer  )
        {
            mMesh->Draw( inCommandBuffer );
        }

        virtual void Update() const override
        {
        }

        virtual burst::Presenter & GetPresenter() const override
        {
            return ( burst::Presenter & ) mPresenter;
        }

    private:
        grs::MeshPresenter mPresenter;
        vkt::MeshPtr mMesh;
};

int main()
{
    auto engine = GearsEngine( 900, 900, "Gears" );
    engine.Run();
}