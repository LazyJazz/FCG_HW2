#pragma once
#include "app.h"
#include "buffer.h"
#include "celestial_body.h"
#include "entity.h"
#include "font_factory.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "model.h"
#include "texture_image.h"

struct GlobalUniformObject {
  glm::mat4 proj;
  glm::mat4 world;
};

class SolarSystem : public Application {
 public:
  SolarSystem();
  [[nodiscard]] Model *GetSphereModel() const {
    return sphere_.get();
  }

  [[nodiscard]] vulkan::PipelineLayout *EntityPipelineLayout() const {
    return entity_pipeline_layout_.get();
  }

  [[nodiscard]] FontFactory *GetFontFactory() const {
    return font_factory_.get();
  }

 private:
  void OnInitImpl() override;
  void OnUpdateImpl() override;
  void OnRenderImpl(VkCommandBuffer cmd_buffer) override;
  void OnShutdownImpl() override;

  void CreateEntityPipelineAssets();
  void CreateGlobalAssets();
  void CreateEntities();
  void CreateFontFactory();
  void CreateCelestialBodies();

  void DestroyEntityPipelineAssets();
  void DestroyGlobalAssets();
  void DestroyEntities();
  void DestroyFontFactory();
  void DestroyCelestialBodies();

  void KeyCallBack(int key, int scancode, int action, int mods);

  std::shared_ptr<vulkan::DescriptorPool> descriptor_pool_;
  std::shared_ptr<vulkan::DescriptorSetLayout> descriptor_set_layout_;
  std::shared_ptr<vulkan::DescriptorSet> descriptor_set_;

  std::shared_ptr<vulkan::ShaderModule> entity_vert_shader_;
  std::shared_ptr<vulkan::ShaderModule> entity_frag_shader_;
  std::shared_ptr<vulkan::PipelineLayout> entity_pipeline_layout_;
  std::shared_ptr<vulkan::Pipeline> entity_pipeline_;

  std::unique_ptr<Model> triangle_;
  std::unique_ptr<TextureImage> triangle_texture_image_;
  std::unique_ptr<Entity> triangle_entity_;

  std::unique_ptr<Model> sphere_;

  std::unique_ptr<vulkan::DescriptorSetLayout> global_descriptor_set_layout_;
  std::unique_ptr<vulkan::DescriptorPool> global_descriptor_pool_;
  std::vector<std::unique_ptr<vulkan::DescriptorSet>> global_descriptor_sets_;
  std::unique_ptr<DynamicBuffer<GlobalUniformObject>> global_uniform_buffer_;

  GlobalUniformObject global_uniform_object_;

  std::unique_ptr<class CelestialBody> sun_;
  std::unique_ptr<class CelestialBody> mercury_;
  std::unique_ptr<class CelestialBody> venus_;
  std::unique_ptr<class CelestialBody> earth_;
  std::unique_ptr<class CelestialBody> mars_;
  std::unique_ptr<class CelestialBody> jupiter_;
  std::unique_ptr<class CelestialBody> saturn_;
  std::unique_ptr<class CelestialBody> uranus_;
  std::unique_ptr<class CelestialBody> neptune_;
  std::unique_ptr<class CelestialBody> moon_;

  std::vector<CelestialBody *> planets_;

  std::unique_ptr<FontFactory> font_factory_;

  std::string font_types_[2];
  int font_select_{0};
  float global_t_{0.0f};
  float camera_theta_{0.0f};
  float time_flowing_ratio_{1.0f};
  bool show_planet_name_{true};
  bool show_usage_info_{true};
};
