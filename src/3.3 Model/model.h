#include <shader_loader.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <mesh.h>

class Model
{
public:
    Model(char *path)
    {
    }
    void Draw(ShaderLoader shader);

private:
    vector<Mesh> meshes;
    string directory;

    void loadModel(string path);
    void processNode(aiNode *node, const aiScene *scene);
    void processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTexture(aiMaterial *mat, aiTextureType type, string typeName);
};