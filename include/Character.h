class Character {
protected:
  Vector2 position;
  Vector2 moveTarget;
  bool movingToTarget;

  float speed;
  int currentFrame;
  float animationTimer;
  float animationSpeed;

public:
  Character(float x, float y);

  virtual void Update();
  virtual void Draw();

  Vector2 GetPosition() const;
  void SetTarget(Vector2 target);
};