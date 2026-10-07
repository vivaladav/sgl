#pragma once

namespace sgl
{
namespace graphic
{

class Particle
{
public:
    Particle() = default;
    virtual ~Particle() = default;

    bool IsActive() const;
    void SetActive(bool val);

    virtual void Update(float delta) = 0;

    bool IsDone() const;
    void ClearDone();
    void SetDone();

    bool HasDelay() const;
    float GetDelay() const;
    void SetDelay(float val);

    virtual void Render() = 0;

private:
    virtual void OnDone();

private:
    float mDelay = 0.f;
    bool mActive = true;
    bool mDone = false;
};

// ==================== INLINE FUNCTIONS ====================

inline bool Particle::IsActive() const { return mActive; }
inline void Particle::SetActive(bool val) { mActive = val; }

inline bool Particle::IsDone() const { return mDone; }
inline void Particle::ClearDone() { mDone = false; }
inline void Particle::SetDone()
{
    mDone = true;
    OnDone();
}

inline bool Particle::HasDelay() const { return mDelay > 0.f; }
inline float Particle::GetDelay() const { return mDelay; }
inline void Particle::SetDelay(float val) { mDelay = val; }

inline void Particle::OnDone() { }

} // namespace graphic
} // namespace sgl
