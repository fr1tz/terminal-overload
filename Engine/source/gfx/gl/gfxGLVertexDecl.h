#ifndef GFX_GL_VERTEX_DECL
#define GFX_GL_VERTEX_DECL

class GFXVertexFormat;
class GFXGLDevice;

class GFXGLVertexDecl : public GFXVertexDecl
{
public:
   GFXGLVertexDecl() : mFormat(NULL), mVertexAttribActiveMask(0) {}
   void set(const GFXVertexFormat *format)
   {
      mFormat = format;

      if(!glVerticesFormat.size())
      {
         for(int i = 0; i < 4; ++i)
         _initVerticesFormat(i);
      }
   }

   void prepare_old(U32 stream, GLint mBuffer, GLint mDivisor) const;
   void updateActiveVertexAttrib_old(U32 lastActiveMask) const;

   struct glVertexAttribData
   {
      U32 stream;
      GLint attrIndex;
      GLint elementCount; // 1 - 4
      GLenum type; // GL_FLOAT...
      GLboolean normalized;
      GLsizei stride;
      GLvoid *pointerFirst;
   };
   
protected:
   friend class GFXGLDevice;
   const GFXVertexFormat *mFormat;
   U32 mVertexAttribActiveMask;
   Vector<glVertexAttribData> glVerticesFormat;

   void _initVerticesFormat(U32 stream);
};

#endif //GFX_GL_VERTEX_DECL