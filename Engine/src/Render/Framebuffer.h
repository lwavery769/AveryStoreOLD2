#pragma once

#include <cstdint>
namespace ALStore {

	struct FramebufferSpecification
	{
		uint32_t Width, Height;
		// FramebufferFormat Format = 
		uint32_t Samples = 1;

		bool SwapChainTarget = false; //Render to screen or frame bnuffer -- ?
	};
	class Framebuffer
	{
	public:
		Framebuffer(const FramebufferSpecification& spec);
		~Framebuffer();

		void Invalidate();

		void Bind();
		void Unbind();
		void Resize(uint32_t width, uint32_t height);

		uint32_t GetColorAttachmentRendererID() const { return m_ColorAttachment1; }

		const FramebufferSpecification& GetSpecification() const { return m_Specification; }
		struct PixelInfo {
			uint32_t ObjectID = 0;
			uint32_t DrawID = 0;
			uint32_t PrimID = 0;

			void Print()
			{
				printf("Object %d draw %d prim %d\n", ObjectID, DrawID, PrimID);
			}
		};

		void ClearAttachment( int value);
		PixelInfo ReadPixel(unsigned int x, unsigned int y);
	private:
		uint32_t m_RendererID = 0;
		uint32_t m_ColorAttachment1 = 0, m_ColorAttachment2 = 0, m_DepthAttachment = 0;
		FramebufferSpecification m_Specification;
	};
}