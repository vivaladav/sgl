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

    virtual void Render() = 0;

private:
    virtual void OnDone();

private:
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

inline void Particle::OnDone() { }

} // namespace graphic
} // namespace sgl
