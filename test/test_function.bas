FUNCTION DAdd(p)
    DIM psum
    IF p > 1 THEN
        psum = p + DAdd(p - 1)
    ELSE
        psum = psum + p
    END If
    DAdd = psum
END FUNCTION