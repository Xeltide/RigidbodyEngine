#include "Shader.h"

Shader::Shader(string name, string filePath) {
	mName = name;
	mFilePath = filePath;
}

void Shader::Load(ID3D11Device1* direct3DDevice) {
	// Load in the effect (shader) file and compile it
	ID3D10Blob* compiledShader = nullptr;
	ID3D10Blob* errorMessages = nullptr;
	HRESULT hr = D3DCompileFromFile(wstring(mFilePath.begin(), mFilePath.end()).c_str(), nullptr, nullptr, nullptr, "fx_5_0", 0, 0, &compiledShader, &errorMessages);
	if (FAILED(hr))
	{
		ReleaseObject(errorMessages);
	}

	// Create an effect object from the compiled shader
	hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(), compiledShader->GetBufferSize(), 0, direct3DDevice, &mEffect);
	if (FAILED(hr))
	{
		//throw GameException("D3DX11CreateEffectFromMemory() failed.", hr);
	}

	ReleaseObject(compiledShader);

	//ID3DX11EffectVariable* variable = mEffect->GetVariableByName("WorldViewProjection");
	//if (variable == nullptr)
	//{
		//throw GameException("ID3DX11Effect::GetVariableByName() could not find the specified variable.", hr);
	//}
	//As the variable is the WVP which is a matrix, need to have it returned (cast) as a matrix type
	//mWvpVariable = variable->AsMatrix();
	//if (mWvpVariable->IsValid() == false)
	//{
		//throw GameException("Invalid effect variable cast.");
	//}
}

ID3DX11EffectPass* Shader::GetPass() {
	return mPass;
}

ID3DX11Effect* Shader::GetEffect() {
	return mEffect;
}

void Shader::SetTechPass(const char* techName, const char* passName) {
	// Look up the technique, pass, and WVP variable from the effect
	//each technique contains one or more passes
	//each pass consists of setting one or more texture stage registers of the 3D hardware
	//Often a fallback pass is provided for older hardware
	//Initial pass might render water, specular highlights, caustic textures, lighting
	//Second pass might do the above but no lighting (assuming older hardware not supporting this)
	//Thus first pass is tried, if it fails, second pass is tried
	//Variables can be passed to GPU for effect functions e.g. the WorldViewProjection (WVP) in this case
	//which is needed for the vertex shader to move vertices into the world view
	mTechnique = mEffect->GetTechniqueByName(techName);
	if (mTechnique == nullptr)
	{
		//throw GameException("ID3DX11Effect::GetTechniqueByName() could not find the specified technique.", hr);
	}

	mPass = mTechnique->GetPassByName(passName);
	if (mPass == nullptr)
	{
		//throw GameException("ID3DX11EffectTechnique::GetPassByName() could not find the specified pass.", hr);
	}
}

void Shader::SetInputLayout(ID3D11Device1* direct3DDevice, D3D11_INPUT_ELEMENT_DESC inputElementDescriptions[], UINT descNumber) {
	// Create the input layout to map the vertex data from the CPU to the GPU
	//From the pass we obtain the pipeline, signature of the pass (params), stencil etc.
	D3DX11_PASS_DESC passDesc;
	mPass->GetDesc(&passDesc);

	//Now can create the InputLayout to provide the mapping of vertex data from CPU to GPU
	HRESULT hr = direct3DDevice->CreateInputLayout(inputElementDescriptions, descNumber, passDesc.pIAInputSignature, passDesc.IAInputSignatureSize, &mInputLayout);
	if (FAILED(hr))
	{
		//throw GameException("ID3D11Device::CreateInputLayout() failed.", hr);
	}
}